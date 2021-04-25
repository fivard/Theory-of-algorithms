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

    public:
        bool isLeaf{};

        std::vector<Element> elements;
        std::vector<Node*> childs;

        Node* parent;
        Node* leftSibling;
        Node* rightSibling;

        Node(){
            isLeaf = false;
            parent = leftSibling = rightSibling = nullptr;
            childs.clear();
            elements.clear();
        }
        Node(const bool& isLeaf, const std::vector<Element>& elements,
                                 const std::vector<Node*>& childs): Node(){

            this->isLeaf = isLeaf;
            this->elements = elements;
            this->childs = childs;
        }
        bool contain(const K& key){
            if (isLeaf)
                for (auto& i : elements)
                    if (i.key == key)
                        return true;
            return false;
        }

        void print(int spaces){
            if (elements.size() == 0)
                return;

            if (childs[elements.size()] != nullptr)
                childs[elements.size()]->print(spaces+1);
            else {
                for (int j = 0; j < spaces+1; j++)
                    std::cout << "\t";
                std::cout << "null\n";
            }
            for (int i = elements.size() - 1; i >= 0; i--){
                for (int j = 0; j < spaces; j++)
                    std::cout << "\t";
                std::cout << elements[i].key << ":" << elements[i].data << std::endl;
                if (childs[i] != nullptr)
                    childs[i]->print(spaces+1);
                else {
                    for (int j = 0; j < spaces+1; j++)
                        std::cout << "\t";
                    std::cout << "null\n";
                }
            }

        }
    }; ///--------------------------end of class Node

    int power{};
    Node* root;
private:
    void split(Node* toSplit){

        Element midEl = toSplit->elements[power];
        Node* afterSplit = moveHalfNodeToNewOne(toSplit);


        if(toSplit == this->root){
            this->root = new Node(false, {midEl}, {toSplit, afterSplit});
            toSplit->parent = root;
            afterSplit->parent = root;

        } else{

            Node* parent = toSplit->parent;
            afterSplit->parent = parent;

            int pos = 0;
            while(pos < parent->elements.size() && parent->elements[pos].key < midEl.key)
                pos++;


            auto it1 = parent->elements.begin() + pos;
            parent->elements.emplace(it1, midEl);

            auto it2 = parent->childs.begin() + pos + 1;
            parent->childs.emplace(it2, afterSplit);

            if(parent->elements.size() == 2 * power){
                split(parent);
            }
        }
    }
    void erase(Node* toDelete, K key){

    }
    void updateKeys(Node* toUpdate){

        
    }

    [[nodiscard]] Node* findLeaf(Node* node, K toFind){
        if(node->isLeaf){
            return node;
        }

        for(int i = 0; i < node->elements.size(); i++){
            if(toFind < node->elements[i].key){
                return findLeaf(node->childs[i], toFind);
            }
        }

        return findLeaf(node->childs[node->childs.size() - 1], toFind);
    }
    [[nodiscard]] Node* moveHalfNodeToNewOne(Node* toSplit){
        std::vector<Element> elementsSplit;
        std::vector<Node*> childSplit;

        Element midEl = toSplit->elements[power];

        for(int i = 0; i < power - 1; i++){
            elementsSplit.emplace_back(toSplit->elements[i + power + 1]);
            childSplit.emplace_back(toSplit->childs[i + power + 1]);
        }
        childSplit.emplace_back(toSplit->childs[power * 2]);

        if(toSplit->isLeaf){
            elementsSplit.emplace(elementsSplit.begin(), midEl);
            childSplit.emplace(childSplit.begin(), nullptr);
        }

        Node* afterSplit = new Node(toSplit->isLeaf, elementsSplit, childSplit);

        for(int i = 0; i < power; i++){
            toSplit->elements.pop_back();
            toSplit->childs.pop_back();
        }

        afterSplit->rightSibling = toSplit->rightSibling;
        if(afterSplit->rightSibling != nullptr){
            afterSplit->rightSibling->leftSibling = afterSplit;
        }
        toSplit->rightSibling = afterSplit;
        afterSplit->leftSibling = toSplit;

        return afterSplit;
    }

public:
    explicit BPlusTree(const int& power){
        this->power = power;
        root = nullptr;
    }

    void erase(K key){

        Node* toDelete = findLeaf(root, key);

        if(toDelete == root && toDelete->elements.size() == 1){
            root = nullptr;
            return;
        }

        erase(toDelete, key);
    }
    void insert(const K& key, const T& data){

        auto* element = new Element(key, data);

        if(root == nullptr){
            std::vector<Element> vector = {*element};
            root = new Node(true, vector, {nullptr, nullptr});
            return;
        }

        Node* toInsert = findLeaf(root, key);
        int pos = 0;
        while (pos < toInsert->elements.size() && toInsert->elements[pos].key < key)
            pos++;


        auto it = toInsert->elements.begin() + pos;
        toInsert->elements.emplace(it,  *element);
        toInsert->childs.emplace_back(nullptr);

        if(toInsert->elements.size() == power * 2){
            split(toInsert);
        }

    }
    void print(){
        std::cout << "\nTree: \n";
        if (root != nullptr)
            root->print(0);
        else
            std::cout << "Tree is empty\n";
    }

    T search(K key){

        Node* toFind = findLeaf(root, key);

        int pos = 0;
        while (pos < toFind->elements.size() && toFind->elements[pos].key < key)
            pos++;

        return toFind->elements[pos].value;
    }
};

#endif //LAB6_B_TREE__BPLUSTREE_H
