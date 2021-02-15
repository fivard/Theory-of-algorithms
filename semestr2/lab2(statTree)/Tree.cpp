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
Tree::Node::Node(Node *left, Node *right, Node *parent,
           nodeColor color, int data, unsigned int size) {
    _left = left;
    _right = right;
    _parent = parent;
    _color = color;
    _data = data;
    _size = size;
}

void Tree::Node::output(int countTabs) {
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
void Tree::Node::clearMemory(Node* node) {
    if (node != nullptr){
        if (node->_right)
            clearMemory(node->_right);
        if (node->_left)
            clearMemory(node->_left);
        node = nullptr;
    }
}

Tree::Tree() {
    root = nullptr;
}
Tree::~Tree() {
    root->clearMemory(root);
}

void Tree::output() {
    cout << "\nTree:\n";
    root->output(1);
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

void Tree::fixInsertion(Node *node) {
    if (node == root) {
        root->_color = BLACK;
        return;
    }
    node->output(1);
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
                cout << node->_data;
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
        node->_parent->_right = leftSon;
    else
        node->_parent->_left = leftSon;

    leftSon->_right = node;
    node->_parent = leftSon;
}