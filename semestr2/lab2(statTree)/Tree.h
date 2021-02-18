//
// Created by Acer on 14.02.2021.
//

#ifndef LAB2_STATTREE_TREE_H
#define LAB2_STATTREE_TREE_H

#include "MusicStore.h"

typedef enum {BLACK, RED} nodeColor;

class Tree {

    class Node {

    public:
        Node *_left;
        Node *_right;
        Node *_parent;
        nodeColor _color;
        int _data;
        unsigned int _size;

        explicit Node(int data);


        void output(Node *node, int space) const;
    };
    Node* root;
    void clearMemory(Node* node);

    void fixInsertion(Node* node);
    void fixErasing(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);

public:
    Tree();
    ~Tree();
    void insert(int data);
    Node* search(int data);
    Node* getSuccessor(Node* node);
    Node* getMinNode(Node* node) const;
    void output() const;

    void erase(int data);
    void erase(Node* node);
};

#endif //LAB2_STATTREE_TREE_H
