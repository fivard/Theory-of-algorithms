//
// Created by Acer on 14.02.2021.
//

#ifndef LAB2_STATTREE_TREE_H
#define LAB2_STATTREE_TREE_H

#include "MusicStore.h"

typedef enum {BLACK, RED} nodeColor;

class Tree {
public:
    class Node {

    public:
        Node *_left;
        Node *_right;
        Node *_parent;
        nodeColor _color;
        int _data;
        unsigned int _size;

        Node(int data);
        Node(Node *left, Node *right, Node *parent,
             nodeColor color, int data, unsigned int size);

        void clearMemory(Node* node);
        void output(int countTabs);
    };
    Node* root;

    void fixInsertion(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);

    Tree();
    ~Tree();
    void insert(int data);
    void output();
};

#endif //LAB2_STATTREE_TREE_H
