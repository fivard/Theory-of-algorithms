//
// Created by Acer on 14.03.2021.
//

#include "PersistentTree.h"

using namespace std;

PersistentTree::Node::Node(int data) {
    _data = data;
    _color = RED;
    _left = _right = _parent = nullptr;
}
PersistentTree::Node::Node(Node* node, Node* parent){
    _parent = parent;
    _left = node->_left;
    _right= node->_right;
    cout << "constructor - " << _left << ' ' << _right << '\n';
    _data = node->_data;
    _color = node->_color;

    if (node->_left != nullptr)
        node->_left->_parent = this;
    if (node->_right != nullptr)
        node->_right->_parent = this;

    if (parent != nullptr) {
        if (parent->_right == node)
            parent->_right = this;
        else
            parent->_left = this;
    }
}

void PersistentTree::Node::output(Node *node, int space) const {
    if (node == nullptr)
        return;

    space += 10;

    output(node->_right, space);

    cout << std::endl;
    for (int i = 10; i < space; i++)
        cout<<" ";
    cout << node->_data << ":";
    if(node->_color == BLACK)
        cout <<"B";
    else if(node->_color == RED)
        cout << "R";

    output(node->_left, space);
}
void PersistentTree::clearMemory(Node* node) {
    if (node != nullptr){
        if (node->_right)
            clearMemory(node->_right);
        if (node->_left)
            clearMemory(node->_left);

        delete node;
    }
}

PersistentTree::PersistentTree() {
    root = nullptr;
    previousRoots.clear();
}
PersistentTree::~PersistentTree() {
    //for (auto &i : previousRoots)
        //clearMemory(i);
}

PersistentTree::Node* PersistentTree::search(int data) {
    Node* temp   = new Node(root, nullptr);
    root         = temp;

    while (temp != nullptr && temp->_data != data){
        if (temp->_data < data)

            if (temp->_right == nullptr)
                temp = nullptr;
            else
                temp = new Node(temp->_right, temp);

        else

            if (temp->_left == nullptr)
                temp = nullptr;
            else
                temp = new Node(temp->_left, temp);

    }
    return temp;
}
PersistentTree::Node* PersistentTree::getSuccessor(Node *node) {
    if (node->_right)
        return getMinNode(node->_right);

    Node* successor = node->_parent;

    while (successor && successor->_right == node) {
        node = successor;
        successor = successor->_parent;
    }

    return successor;
}
PersistentTree::Node* PersistentTree::getMinNode(Node *node) const{
    while (node && node->_left)
        node = new Node(node->_left, node);

    return node;
}

void PersistentTree::insert(int data) {
    Node *node = new Node(data);
    if (root == nullptr){
        root          = node;
        root->_parent = nullptr;

        previousRoots.push_back(root);
        fixInsertion(root);
        return;
    }

    Node* temp   = new Node(root, nullptr);
    root         = temp;
    Node* parent;

    while (temp != nullptr){
        parent = temp;
        if (temp->_data < node->_data)
            if (temp->_right == nullptr)
                temp = nullptr;
            else
                temp = new Node(temp->_right, temp);
        else
            if (temp->_left == nullptr)
                temp = nullptr;
            else
                temp = new Node(temp->_left, temp);
    }

    node->_parent = parent;

    if (parent->_data > node->_data)
        parent->_left = node;
    else
        parent->_right = node;

    fixInsertion(node);

    previousRoots.push_back(root);
}

void PersistentTree::erase(int data){
    Node* node = search(data);

    if (node == nullptr){
        cout << "There isn't vertex with given data\n";
        return;
    }

    cout << "AFTER SEARCHING\n";
    Dump();

    erase(node);
}
void PersistentTree::erase(Node *node) {
    if (node == root && node->_left == nullptr && node->_right == nullptr){
        clearMemory(root);
        root = nullptr;
        previousRoots.push_back(nullptr);
        return;
    }

    Node* tempNode;
    Node* parent = node->_parent;
    if (node->_color == RED){
        if (node->_right == nullptr && node->_left == nullptr){ // R0
            if (parent->_right == node)
                parent->_right = nullptr;
            else
                parent->_left = nullptr;

            clearMemory(node);
            previousRoots.push_back(root);
            return;
                                                               // R1 not exist
        } else {                                               // R2
            tempNode = getSuccessor(node);
            node->_data = tempNode->_data;
            erase(tempNode);
            return;
        }

    } else {
        if (node->_right == nullptr && node->_left == nullptr){ //B0
            fixErasing(node);
            if (parent->_left == node)
                parent->_left = nullptr;
            else
                parent->_right = nullptr;


            clearMemory(node);
            previousRoots.push_back(root);
            return;
        }

        if (node->_right == nullptr || node->_left == nullptr){ //B1
            if (node->_right != nullptr) {
                node->_data = node->_right->_data;

                clearMemory(node->_right);
                node->_right = nullptr;
            } else {
                node->_data = node->_left->_data;

                clearMemory(node->_left);
                node->_left = nullptr;
            }

            previousRoots.push_back(root);
            return;
        }
        if (node->_right != nullptr && node->_left != nullptr){ //B2
            tempNode = getSuccessor(node);
            node->_data = tempNode->_data;
            erase(tempNode);
            return;
        }
    }
}

void PersistentTree::fixInsertion(Node *node) {
    if (node == root) {
        root->_color = BLACK;
        return;
    }
    while(node->_parent != nullptr && node->_parent->_color == RED){
        if (node->_parent == node->_parent->_parent->_left){
            Node* uncle;
            if (node->_parent->_parent->_right == nullptr)
                uncle = nullptr;
            else
                uncle = new Node(node->_parent->_parent->_right, node->_parent->_parent);

            if (uncle != nullptr && uncle->_color == RED){
                node->_parent->_color = BLACK;
                uncle->_color = BLACK;
                node->_parent->_parent->_color = RED;
                node = node->_parent->_parent;
            } else {
                if (node == node->_parent->_right){
                    node = node->_parent;
                    leftRotate(node);
                }
                node->_parent->_color = BLACK;
                node->_parent->_parent->_color = RED;
                rightRotate(node->_parent->_parent);
            }
        } else {
            Node* uncle;
            if (node->_parent->_parent->_left == nullptr)
                uncle = nullptr;
            else
                uncle = new Node(node->_parent->_parent->_left, node->_parent->_parent);

            if (uncle != nullptr && uncle->_color == RED){
                node->_parent->_color = BLACK;
                uncle->_color = BLACK;
                node->_parent->_parent->_color = RED;
                node = node->_parent->_parent;
            } else {
                if (node == node->_parent->_left){
                    node = node->_parent;
                    rightRotate(node);
                }
                node->_parent->_color = BLACK;
                node->_parent->_parent->_color = RED;

                leftRotate(node->_parent->_parent);
            }
        }
    }
    root->_color = BLACK;
}
void PersistentTree::fixErasing(Node *node) {
    while (node != root && node->_color == BLACK) {
        Node* parent = node->_parent;
        if (parent->_left == node) {
            Node* brother = new Node(parent->_right, parent);

            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;

                leftRotate(parent);
                brother = new Node(parent->_right, parent);
            }
            if ((brother->_left == nullptr || brother->_left->_color == BLACK) &&
                (brother->_right == nullptr || brother->_right->_color == BLACK)) {

                brother->_color = RED;
                node = node->_parent;

            } else {

                if (brother->_right == nullptr || brother->_right->_color == BLACK) {
                    brother->_color = RED;
                    Node* brotherLeft = new Node(brother->_left, brother);
                    brotherLeft->_color = BLACK;

                    rightRotate(brother);
                    brother = new Node(parent->_right, parent);
                }

                brother->_color = parent->_color;
                parent->_color = BLACK;

                if (brother->_right) {
                    Node* brotherRight = new Node(brother->_right, brother);
                    brotherRight->_color = BLACK;
                }

                leftRotate(parent);

                node = root;
            }
        } else {
            Node* brother = new Node(parent->_left, parent);
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;

                rightRotate(parent);
                brother = new Node(parent->_left, parent);
            }

            if ((brother->_left == nullptr || brother->_left->_color == BLACK) &&
                (brother->_right == nullptr || brother->_right->_color == BLACK)) {

                brother->_color = RED;
                node = node->_parent;

            } else {
                if (brother->_left == nullptr || brother->_left->_color == BLACK) {
                    brother->_color = RED;
                    Node* brotherRight = new Node(brother->_right, brother);
                    brotherRight->_color = BLACK;

                    leftRotate(brother);
                    brother = new Node(parent->_left, parent);
                }

                brother->_color = parent->_color;
                parent->_color = BLACK;

                if (brother->_left) {
                    Node* brotherLeft = new Node(brother->_left, brother);
                    brotherLeft->_color = BLACK;
                }

                rightRotate(parent);

                node = root;
            }
        }
    }
    node->_color = BLACK;
}

void PersistentTree::leftRotate(Node *node) {
    Node *rightSon = new Node(node->_right, node);
    node->_right = rightSon->_left;

    if (rightSon->_left != nullptr)
        rightSon->_left->_parent = node;
    rightSon->_parent = node->_parent;
    if (node->_parent == nullptr){
        root = rightSon;
    } else if (node == node->_parent->_left)
        node->_parent->_left = rightSon;
    else
        node->_parent->_right = rightSon;

    rightSon->_left = node;
    node->_parent = rightSon;

}
void PersistentTree::rightRotate(Node *node) {

    Node *leftSon = new Node(node->_left, node);
    node->_left = leftSon->_right;

    if (leftSon->_right != nullptr)
        leftSon->_right->_parent = node;
    leftSon->_parent = node->_parent;
    if (node->_parent == nullptr){
        root = leftSon;
    } else if (node == node->_parent->_left)
        node->_parent->_left = leftSon;
    else
        node->_parent->_right = leftSon;

    leftSon->_right = node;
    node->_parent = leftSon;
}

void PersistentTree::backUpPreviousRoot(Node *newRoot) {
    root = newRoot;
    backUpTree(root);
}
void PersistentTree::backUpTree(Node *node) {
    if (node != nullptr) {
        cout << node << "\n"
             << "node->-left = " << node->_left << '\n'
             << "node->_right = " << node->_right << '\n';
        if (node->_left != nullptr) {
            node->_left->_parent = node;
            backUpTree(node->_left);
        }
        if (node->_right != nullptr) {
            node->_right->_parent = node;
            backUpTree(node->_right);
        }
    }
}

void PersistentTree::output() const {
    cout << "\nTree:\n";
    if (root == nullptr){
        cout << "Tree is empty\n";
        return;
    }
    root->output(root, 0);
}
void PersistentTree::DumpAllRoots() {
    for (int i = 0; i < previousRoots.size(); i++){
        cout << "---------------------------------" << i << "--------------------------\n";
        cout << previousRoots[i] << '\n';
        backUpPreviousRoot(previousRoots[i]);
        cout << previousRoots[i] << '\n';
        Dump();
    }
}
