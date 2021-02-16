//
// Created by Acer on 14.02.2021.
//

#include "Tree.h"

Tree::Node::Node(int data) {
    _data = data;
    _color = RED;
    _size = 1;
    _left = _right = _parent = nullptr;
}

void Tree::Node::output(int countTabs) const {
    cout << _data << " ";
    if (_color == RED)
        cout << "RED" << endl;
    else
        cout << "BLACK" << endl;

    if (_left != nullptr) {
        for (int i = 0; i < countTabs; i++)
            cout << '\t';
        cout << "l: ";
        _left->output(countTabs + 1);
    }
    if (_right != nullptr) {
        for (int i = 0; i < countTabs; i++)
            cout << '\t';
        cout << "r: ";
        _right->output(countTabs + 1);
    }

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

void Tree::output() const {
    cout << "\nTree:\n";
    root->output(1);
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
    Node* y = nullptr;
    while (x != nullptr){
        y = x;
        if (x->_data < node->_data)
            x = x->_right;
        else
            x = x->_left;
    }
    node->_parent = y;
    if (y == nullptr)
        root = node;
    else{
        if (y->_data > node->_data)
            y->_left = node;
        else
            y->_right = node;
    }
    fixInsertion(node);
}
void Tree::erase(int data){
    Node* node = search(data);
    if (node == nullptr){
        cout << "There isn't vertex with given data\n";
        return;
    }

    Node* parent = node->_parent;
    Node* child  = nullptr;
    Node* successor;

    if (node->_left && node->_right) {
        successor = getSuccessor(node);

        node->_data = successor->_data;
        parent = successor->_parent;
        node = successor;

        if (successor->_right)
            child = successor->_right;
    } else if (!node->_left && node->_right) {
        child = node->_right;
    } else if (node->_left && !node->_right) {
        child = node->_left;
    }

    if (parent) {
        if (parent->_left == node)
            parent->_left = child;
        else
            parent->_right = child;

        if (child)
            child->_parent = parent;
    } else {
        root = child;

        if (root)
            root->_parent = nullptr;
    }

    if (node->_color == BLACK && child)
        fixErasing(child);

    node->_left = nullptr;
    node->_right = nullptr;

    delete node;
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
                parent->_color = BLACK;

                leftRotate(parent);
                brother = parent->_right;
            }

            if ((!brother->_left || brother->_left->_color == BLACK) &&
                (!brother->_right || brother->_right->_color == BLACK)) {

                brother->_color = RED;
                node = parent;
                parent = node->_parent;
            } else if (!brother->_right || brother->_right->_color == BLACK) {
                brother->_color = RED;

                rightRotate(brother);
                brother = parent->_right;
            }

            if (parent) {
                brother->_color = parent->_color;
                parent->_color = BLACK;

                if (brother->_right)
                    brother->_right->_color = BLACK;

                leftRotate(parent);
            }

            node = root;
        } else {
            Node* brother = parent->_left;

            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;

                rightRotate(parent);
                brother = parent->_left;
            }

            if ((!brother->_left || brother->_left->_color == BLACK) &&
                (!brother->_right || brother->_right->_color == BLACK)) {

                brother->_color = RED;
                node = parent;
                parent = node->_parent;
            } else if (!brother->_left || brother->_left->_color == BLACK) {
                brother->_color = RED;

                leftRotate(brother);
                brother = parent->_left;
            }

            if (parent) {
                brother->_color = parent->_color;
                parent->_color  = BLACK;

                if (brother->_left)
                    brother->_left->_color = BLACK;

                rightRotate(parent);
            }

            node = root;
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