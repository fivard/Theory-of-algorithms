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
        bool contain(const K key) const{
            for (int i = 0; i < elements.size(); i++)
                if (elements[i].key == key)
                    return true;
            return false;
        }
        int findPosition(const K key) const{
            for (int i = 0; i < elements.size(); i++)
                if (elements[i].key == key)
                    return i;
            return -1;
        }
        int findPositionInChildrenByNode(const Node* node) const{
            for (int i = 0; i < this->childs.size(); i++)
                if (this->childs[i] == node)
                    return i;
            return -1;
        }

        void free(Node* node){
            if (node == nullptr)
                return;

            for (auto i : node->childs)
                free(i);

            delete node;
        }
        void print(int spaces) const{
            if (this == nullptr)
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

        toDelete->elements.erase(toDelete->elements.begin() + toDelete->findPosition(key));

        if (toDelete == root && root->elements.size() == 0) {
            root = nullptr;
            return;
        }

        if (toDelete->elements.size() >= power - 1){
            updateKeys(toDelete->parent, key);
            return;
        }

        Node* left = toDelete->leftSibling;
        Node* right = toDelete->rightSibling;

        if (left != nullptr && left->elements.size() > power - 1 && left->parent == toDelete->parent){
            auto it = toDelete->elements.begin();
            int indexLastElement = left->elements.size() - 1;

            int pos = left->parent->findPositionInChildrenByNode(left);
            toDelete->elements.template emplace(it, left->elements[indexLastElement]);
            left->parent->elements[pos] = toDelete->elements[0];
            left->elements.pop_back();

            updateKeys(toDelete->parent, key);

            return;
        }

        if (right != nullptr && right->elements.size() > power - 1 && right->parent == toDelete->parent){
            int keyBorrowedElement = right->elements[0].key;

            toDelete->elements.template emplace_back(right->elements[0]);
            right->elements.erase(right->elements.begin());

            int pos = toDelete->parent->findPosition(keyBorrowedElement);
            toDelete->parent->elements[pos] = right->elements[0];

            updateKeys(toDelete->parent, key);

            return;
        }

        if (left != nullptr && left->parent == toDelete->parent){
            mergeLeafs(left, toDelete);
            updateKeys(left->parent, key);
        }

        if (right != nullptr && right->parent == toDelete->parent){
            mergeLeafs(toDelete, right);
            updateKeys(toDelete->parent, key);
        }

    }
    void updateKeys(Node* toUpdate, const K key){
        if (toUpdate == nullptr)
            return;

        if (toUpdate->contain(key)){
            Element successor = getSuccessor(toUpdate, key);
            int pos = toUpdate->findPosition(key);

            toUpdate->elements[pos] = successor;
        }
        if (toUpdate->elements.size() < power - 1 && toUpdate != root){
            Node* left = toUpdate->leftSibling;
            Node* right = toUpdate->rightSibling;

            if (left != nullptr && left->elements.size() > power - 1 && left->parent == toUpdate->parent){
                borrowElementInternal(toUpdate, left);
            } else if (right != nullptr && right->elements.size() > power - 1 && right->parent == toUpdate->parent){
                borrowElementInternal(toUpdate, right);
            } else {
                if (left != nullptr && left->parent == toUpdate->parent){
                    mergeWithParent(toUpdate, left);
                } else {
                    mergeWithParent(toUpdate, right);
                }
            }
        }

        updateKeys(toUpdate->parent, key);
    }
    void mergeLeafs(Node* left, Node* right){
        Node* parent = right->parent;

        for (int i = 0; i < right->elements.size(); i++){
            left->elements.template emplace_back(right->elements[i]);
        }

        if (right->rightSibling != nullptr)
            right->rightSibling->leftSibling = left;
        left->rightSibling = right->rightSibling;

        int minRightKey = right->elements[0].key;
        int pos = parent->findPosition(minRightKey);

        parent->elements.erase(parent->elements.begin() + pos);
        parent->childs.erase(parent->childs.begin() + pos + 1);

        if (parent == root && parent->elements.size() == 0){
            root = left;
            left->parent = right->parent = nullptr;
        }
        delete right;
    }
    void borrowElementInternal(Node* toUpdate, Node* sibling){
        Node* parent = toUpdate->parent;

        if (sibling == toUpdate->leftSibling){
            int pos = 0;
            for (int i = 0; i < parent->childs.size(); i++)
                if (parent->childs[i] == toUpdate)
                    pos = i;

            toUpdate->elements.template emplace(toUpdate->elements.begin(), parent->elements[pos - 1]);
            parent->elements[pos - 1] = sibling->elements[sibling->elements.size() - 1];
            toUpdate->childs.template emplace(toUpdate->childs.begin(), sibling->childs[sibling->childs.size() - 1]);

            sibling->elements.pop_back();
            sibling->childs.pop_back();

            toUpdate->childs[0]->parent = toUpdate;
        } else {
            int pos = 0;
            for (int i = 0; i < parent->childs.size(); i++)
                if (parent->childs[i] == toUpdate)
                    pos = i;


            toUpdate->elements.template emplace_back(parent->elements[pos]);
            parent->elements[pos] = sibling->elements[0];
            toUpdate->childs.template emplace_back(sibling->childs[0]);

            sibling->elements.erase(sibling->elements.begin());
            sibling->childs.erase(sibling->childs.begin());

            toUpdate->childs[toUpdate->childs.size() - 1]->parent = toUpdate;
        }
    }
    void mergeWithParent(Node* toUpdate, Node* sibling){
        Node* parent = toUpdate->parent;

        if (sibling == toUpdate->leftSibling){
            int pos = parent->findPositionInChildrenByNode(toUpdate);

            sibling->elements.template emplace_back(parent->elements[pos - 1]);
            for (int i = 0; i < toUpdate->elements.size(); i++)
                sibling->elements.template emplace_back(toUpdate->elements[i]);
            for (int i = 0; i < toUpdate->childs.size(); i++){
                sibling->childs.template emplace_back(toUpdate->childs[i]);
                toUpdate->childs[i]->parent = sibling;
            }

            if (toUpdate->rightSibling != nullptr)
                toUpdate->rightSibling->leftSibling = sibling;
            sibling->rightSibling = toUpdate->rightSibling;

            parent->elements.erase(parent->elements.begin() + pos - 1);
            parent->childs.erase(parent->childs.begin() + pos);

        } else {
            int pos = parent->findPositionInChildrenByNode(sibling);

            toUpdate->elements.template emplace_back(parent->elements[pos - 1]);
            for (int i = 0; i < sibling->elements.size(); i++)
                toUpdate->elements.template emplace_back(sibling->elements[i]);
            for (int i = 0; i < sibling->childs.size(); i++){
                toUpdate->childs.template emplace_back(sibling->childs[i]);
                sibling->childs[i]->parent = toUpdate;
            }

            if (sibling->rightSibling != nullptr)
                sibling->rightSibling->leftSibling = toUpdate;
            toUpdate->rightSibling = sibling->rightSibling;

            parent->elements.erase(parent->elements.begin() + pos - 1);
            parent->childs.erase(parent->childs.begin() + pos);

        }

        if (parent == root && parent->elements.size() == 0){
            if (sibling == toUpdate->leftSibling)
                root = sibling;
            else
                root = toUpdate;
            sibling->parent = toUpdate->parent = nullptr;
            delete parent;
        }
    }

    Element getSuccessor(Node* node, K key){
        int pos = node->findPosition(key);
        return getMin(node->childs[pos + 1]);
    }
    Element getMin(Node* node){
        if (node == nullptr)
            return {0,0};

        if (node->isLeaf)
            return node->elements[0];

        return getMin(node->childs[0]);
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

        for (int i = 0; i < afterSplit->childs.size(); i++) {
            if (afterSplit->childs[i] != nullptr)
                afterSplit->childs[i]->parent = afterSplit;
        }

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
    ~BPlusTree(){
        root->free(root);
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

        return toFind->elements[pos].data;
    }
};

#endif //LAB6_B_TREE__BPLUSTREE_H
