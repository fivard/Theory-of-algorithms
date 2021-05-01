//
// Created by Acer on 05.04.2021.
//

#ifndef LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H
#define LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H

#include <iostream>
#include <algorithm>
#include <cmath>

const int INF = 10e6;

template <class T>
class FibonacciHeap;

template <typename T>
class Node{
private:
    T value;
    Node* parent;
    Node* left;
    Node* right;
    Node* child;
    bool mark{};
    int degree{};

public:
             Node(){
        value = 0;
        mark = false;
        parent = child = nullptr;
        left = right = this;
        degree = 0;
    }
    explicit Node(T newValue){
        value = newValue;
        mark = false;
        parent = child = nullptr;
        left = right = this;
        degree = 0;
    }
            ~Node() = default;

    void print         (int countTabs, Node<T> *head) const{

        for (int i = 0; i < countTabs; i++)
            std::cout << '\t';
        std::cout << value << ":" << degree << ":" << mark;
        if (child != nullptr) {
            std::cout << std::endl;
            child->print(countTabs + 1, child);
        }
        if (left != head) {
            std::cout << std::endl;
            left->print(countTabs, head);
        }
    }
    void clear         (Node<T>* head) {
        if (this != nullptr){
            if (child != nullptr)
                child->clear(child);
            if (left != head)
                left->clear(head);
            delete this;
        }
    }
    void insertBetween (Node<T> *_left, Node<T> *_right){
        _left->right = _right->left = this;
        this->right  = _right;
        this->left   = _left;
    }
    void extractBetween(){
        left->right = right;
        right->left = left;
        left = right = nullptr;
    }

    friend std::ostream& operator<< (std::ostream &out, const Node &node){
        out << node.value;
        return out;
    }
    T values(){
        return value;
    }

    friend FibonacciHeap<T>;
};

template <typename T>
class FibonacciHeap{
private:
    Node<T>* min;
    int countNodes{};

    void cut         (Node<T> *son, Node<T> *parent){
        if (son == son->right)
            parent->child = nullptr;
        else
            parent->child = son->right;

        parent->degree--;

        son->parent = nullptr;
        son->extractBetween();
        son->insertBetween(min, min->right);
        son->mark = false;
    }
    void cascadingCut(Node<T> *node){
        Node<T> *parent = node->parent;
        if (parent != nullptr){
            if (node->mark == false)
                node->mark = true;
            else{
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }
    void consolidate (){
        int size = round(std::log(countNodes))+2;

        auto array = new Node<T>*[size];
        for (int i = 0; i < size; i++)
            array[i] = nullptr;

        Node<T>* temp = min, *rightSibling = nullptr;
        do{
            rightSibling = temp->right;

            Node<T> *x = temp;
            int degree = x->degree;
            while (array[degree] != nullptr){
                Node<T> *y = array[degree];
                if (x->value > y->value){
                    auto z = x;
                    x = y;
                    y = z;
                }
                link(y, x);
                array[degree] = nullptr;
                degree++;
            }
            array[degree] = x;

            while (min->parent != nullptr)
                min = min->parent;

            temp = rightSibling;
            if (rightSibling->parent != nullptr)
                temp = min;
        } while (temp != min);

        for (int i = 0; i < size; i++){
            if (array[i] != nullptr){
                if (min->value > array[i]->value)
                    min = array[i];
            }
        }
    }
    void link        (Node<T> *lower, Node<T> *higher){
        lower->extractBetween();
        if (higher->child == nullptr) {
            higher->child = lower;
            lower->right = lower->left = lower;
        }
        else {
            lower->insertBetween(higher->child, higher->child->right);
        }

        lower->parent = higher;
        higher->degree++;
        lower->mark = false;
    }
    void unionHeaps (FibonacciHeap<T> *first, FibonacciHeap<T> *second){
        if (first->min == nullptr && second->min == nullptr)
            return;
        if (first->min == nullptr) {
            min = second->min;
            countNodes = second->countNodes;
            return;
        }
        if (second->min == nullptr) {
            min = first->min;
            countNodes = first->countNodes;
            return;
        }
        min = std::min(first->min, second->min);

        Node<T> *rightSiblingFirst = first->min->right;
        Node<T> *leftSiblingSecond = second->min->left;

        first->min->right        = second->min;
        second->min->left        = first->min;
        rightSiblingFirst->left  = leftSiblingSecond;
        leftSiblingSecond->right = rightSiblingFirst;

        countNodes = first->countNodes + second->countNodes;

        second->min = nullptr;
    }

public:
             FibonacciHeap(){
        min = nullptr;
        countNodes = 0;
    }
    explicit FibonacciHeap(T value): FibonacciHeap(){
        min = new Node<T>(value);
    }
            ~FibonacciHeap(){
        if (min != nullptr) {
            min->clear(min);
        }
    }

    void print      () const{
        if (min != nullptr)
            min->print(0, min);
        else
            std::cout << "Heap is empty";
        std::cout << "\nCount nodes = " << countNodes << '\n';
    }
    void extractMin (){
        Node<T> *head = min;
        if (head != nullptr){
            if (head->child != nullptr) {
                Node<T> *temp = head->child, *rightSibling = nullptr;
                do {
                    rightSibling = temp->right;
                    temp->parent = nullptr;
                    temp->extractBetween();
                    temp->insertBetween(min->left, min);
                    temp = rightSibling;
                } while (temp != head->child);
            }


            if (head == head->right)
                min = nullptr;
            else{
                min = head->right;
                head->extractBetween();
                consolidate();
            }
            countNodes--;
        }
        head->child = nullptr;
        head->clear(head);
    }
    void decreaseKey(Node<T> *node, T newValue){
        if (newValue > node->value)
            return;
        node->value = newValue;
        Node<T> *parent = node->parent;
        if (parent != nullptr && node->value < parent->value){
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->value < min->value)
            min = node;
    }
    void deleteNode (Node<T> *node){
        decreaseKey(node, -INF);
        extractMin();
    }

    Node<T>*      insert(T value){
        auto node = new Node<T>(value);
        return insert(node);
    }
    Node<T>*      insert(Node<T> *node){
        countNodes++;
        if (min == nullptr){

            min = node;
            return node;
        }
        if (min->left == min){

            min->left   = node;
            min->right  = node;
            node->right = min;
            node->left  = min;

        } else {
            Node<T>* leftSibling = min->left;

            leftSibling->right   = node;
            min->left            = node;
            node->right          = min;
            node->left           = leftSibling;
        }
        if (node->value < min->value)
            min = node;
        return node;
    }
    bool          empty(){
        return min == nullptr;
    }
    [[nodiscard]] Node<T>* minimum(){
        return min;
    }
};

#endif //LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H
