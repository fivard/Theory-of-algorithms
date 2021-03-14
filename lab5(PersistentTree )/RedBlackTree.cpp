//
// Created by Acer on 14.03.2021.
//

#include "RedBlackTree.h"

using namespace std;

Tree::Node::Node(int data) {
    _data = data;
    _color = RED;
    _left = _right = _parent = nullptr;
}

void Tree::Node::output(Node *node, int space) const {
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
void Tree::clearMemory(Node* node) {
    if (node != nullptr){
        if (node->_right)
            clearMemory(node->_right);
        if (node->_left)
            clearMemory(node->_left);
        delete node;
    }
}

Tree::Tree() {
    root = nullptr;
}
Tree::~Tree() {
    clearMemory(root);
}


Tree::Node* Tree::search(int data) {
    Node* temp = root;
    while (temp != nullptr && temp->_data != data){
        if (temp->_data > data)
            temp = temp->_left;
        else
            temp = temp->_right;
    }
    return temp;
}
Tree::Node* Tree::getSuccessor(Node *node) {
    if (node->_right)
        return getMinNode(node->_right);

    Node* successor = node->_parent;

    while (successor && successor->_right == node) {
        node = successor;
        successor = successor->_parent;
    }

    return successor;
}
Tree::Node* Tree::getMinNode(Node *node) const{
    while (node && node->_left)
        node = node->_left;

    return node;
}

void Tree::insert(int data) {
    Node *node = new Node(data);
    if (root == nullptr){
        root = node;
        root->_parent = nullptr;
        fixInsertion(root);
        return;
    }

    Node* x = root;
    Node* parent = nullptr;
    while (x != nullptr){
        parent = x;
        if (x->_data < node->_data)
            x = x->_right;
        else
            x = x->_left;
    }
    node->_parent = parent;
    if (parent == nullptr)
        root = node;
    else{
        if (parent->_data > node->_data)
            parent->_left = node;
        else
            parent->_right = node;
    }

    fixInsertion(node);
}

void Tree::erase(int data){
    Node* node = search(data);

    if (node == nullptr){
        cout << "There isn't vertex with given data\n";
        return;
    }

    erase(node);
}
void Tree::erase(Node *node) {
    if (node == root && node->_left == nullptr && node->_right == nullptr){
        clearMemory(root);
        root = nullptr;
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
            return;
        }

        if (node->_right == nullptr || node->_left == nullptr){ //B1
            parent = node;
            if (node->_right != nullptr) {
                node->_data = node->_right->_data;

                clearMemory(node->_right);
                node->_right = nullptr;
            } else {
                node->_data = node->_left->_data;

                clearMemory(node->_left);
                node->_left = nullptr;
            }

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

void Tree::fixInsertion(Node *node) {
    if (node == root) {
        root->_color = BLACK;
        return;
    }
    while(node->_parent != nullptr && node->_parent->_color == RED){
        if (node->_parent == node->_parent->_parent->_left){
            Node* uncle = node->_parent->_parent->_right;
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
            Node* uncle = node->_parent->_parent->_left;
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
void Tree::fixErasing(Node *node) {
    while (node != root && node->_color == BLACK) {
        Node* parent = node->_parent;
        if (parent->_left == node) {
            Node* brother = parent->_right;
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;

                leftRotate(parent);
                brother = parent->_right;
            }
            if ((brother->_left == nullptr || brother->_left->_color == BLACK) &&
                (brother->_right == nullptr || brother->_right->_color == BLACK)) {
                brother->_color = RED;
                node = node->_parent;

            } else {
                if (brother->_right == nullptr || brother->_right->_color == BLACK) {
                    brother->_color = RED;
                    brother->_left->_color = BLACK;

                    rightRotate(brother);
                    brother = parent->_right;
                }

                brother->_color = parent->_color;
                parent->_color = BLACK;

                if (brother->_right)
                    brother->_right->_color = BLACK;

                leftRotate(parent);

                node = root;
            }
        } else {
            Node* brother = parent->_left;
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;

                rightRotate(parent);
                brother = parent->_left;
            }

            if ((brother->_left == nullptr || brother->_left->_color == BLACK) &&
                (brother->_right == nullptr || brother->_right->_color == BLACK)) {
                brother->_color = RED;
                node = node->_parent;

            } else {
                if (brother->_left == nullptr || brother->_left->_color == BLACK) {
                    brother->_color = RED;
                    brother->_right->_color = BLACK;

                    leftRotate(brother);
                    brother = parent->_left;
                }

                brother->_color = parent->_color;
                parent->_color = BLACK;

                if (brother->_left)
                    brother->_left->_color = BLACK;

                rightRotate(parent);

                node = root;
            }
        }
    }
    node->_color = BLACK;
}

void Tree::leftRotate(Node *node) {
    Node *rightSon = node->_right;
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
void Tree::rightRotate(Node *node) {

    Node *leftSon = node->_left;
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

void Tree::output() const {
    cout << "\nTree:\n";
    if (root == nullptr){
        cout << "Tree is empty\n";
        return;
    }
    root->output(root, 0);
}
