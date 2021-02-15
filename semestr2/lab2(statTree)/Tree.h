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


        void output(int countTabs) const;
    };
    Node* root;
    void clearMemory(Node* node);

    void fixInsertion(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);

public:
    Tree();
    ~Tree();
    void insert(int data);
    Node* search(int data);
    
    void output() const;
};

#endif //LAB2_STATTREE_TREE_H
