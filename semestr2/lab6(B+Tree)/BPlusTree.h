//
// Created by Acer on 09.04.2021.
//

#ifndef LAB6_B_TREE__BPLUSTREE_H
#define LAB6_B_TREE__BPLUSTREE_H

#include <iostream>
#include <vector>

template <class T, class K>
class BPlusTree{
private:
    class Element{///-------------------- class Element
    public:
        T data;
        K key{};

        Element(K key, T data){
            this->key = key;
            this->data = data;
        }
    }; /// ------------------------------ end of class Element

    class Node{ ///---------------------- class Node

        bool leaf{};

        std::vector<Element> elements;
        std::vector<Node*> childs;

        Node* parent;
        Node* leftSibling;
        Node* rightSibling;

    public:
        Node(){
            leaf = false;
            parent = leftSibling = rightSibling = nullptr;
            childs.clear();
            elements.clear();
        }
        Node(const bool& isLeaf, const std::vector<Element>& elements,
                                 const std::vector<Node*>& child): Node(){

            this->isLeaf = isLeaf;
            this->elements = elements;
            this->child = child;
        }
    }; ///--------------------------end of class Node

    int power{};
    Node* root;
private:


public:
    BPlusTree(){
        power = 0;
        root = nullptr;
    }
    explicit BPlusTree(const int& power){
        this->power = power;
        root = nullptr;
    }


};

#endif //LAB6_B_TREE__BPLUSTREE_H
