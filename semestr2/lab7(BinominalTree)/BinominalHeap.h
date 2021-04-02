//
// Created by Acer on 02.04.2021.
//

#ifndef LAB7_BINOMINALTREE__BINOMINALHEAP_H
#define LAB7_BINOMINALTREE__BINOMINALHEAP_H

template <class T>
class BinominalHeap {
private:

    class Node{
    public:
        Node* parent;
        Node* sibling;
        Node* child;
        T     value;
        int   degree{};

        Node(){
            parent = sibling = child = nullptr;
            value = degree = 0;
        }
        explicit Node(T newValue): Node(){
            value = newValue;
        }

        void print(int countTabs) const{
            for (int i = 0; i < countTabs; i++)
                std::cout << '\t';
            std::cout << value;
            if (child != nullptr) {
                std::cout << std::endl;
                child->print(countTabs + 1);
            }
            if (sibling != nullptr){
                std::cout << std::endl;
                sibling->print(countTabs);
            }
            std::cout << std::endl;
        }
        void link(Node* other){
            this->parent = other;
            this->sibling = other->child;
            other->child = this;
            other->degree++;
        }
    };

    Node* head;

public:
    BinominalHeap(){
        head = nullptr;
    }
    explicit BinominalHeap(T newValue){
        head = new Node(newValue);
    }
    ~BinominalHeap() = default;

    void printBinominalHeap() const{
        head->print(0);
    }
    void mergeBinominalHeap(BinominalHeap<T> *first, BinominalHeap<T> *second) {
        Node *firstTemp = first->head,
            *secondTemp = second->head;

        if (firstTemp->degree <= secondTemp->degree) {
            head       = firstTemp;
            firstTemp  = firstTemp->sibling;
        } else {
            head       = secondTemp;
            secondTemp = secondTemp->sibling;
        }

        Node *temp = head;

        while (firstTemp != nullptr && secondTemp != nullptr){
            if (firstTemp->degree < secondTemp->degree) {
                temp->sibling = firstTemp;
                temp          = temp->sibling;
                firstTemp     = firstTemp->sibling;
            } else {
                temp->sibling = secondTemp;
                temp          = temp->sibling;
                secondTemp    = secondTemp->sibling;
            }
        }

        while (firstTemp != nullptr){
            temp->sibling = firstTemp;
            temp          = temp->sibling;
            firstTemp     = firstTemp->sibling;
        }

        while (secondTemp != nullptr){
            temp->sibling = secondTemp;
            temp          = temp->sibling;
            secondTemp    = secondTemp->sibling;
        }
    }
    void unionBinominalHeap(BinominalHeap<T> *first, BinominalHeap<T> *second){
        mergeBinominalHeap(first, second);

        if (head == nullptr)
            return;

        Node *prevX = nullptr,
             *X     = head,
             *nextX = X->sibling;

        while (nextX != nullptr){

            if (X->degree != nextX->degree || (nextX->sibling != nullptr && nextX->sibling->degree == X->degree)){
                prevX = X;
                X     = nextX;

            } else if (X->value <= nextX->value){

                X->sibling = nextX->sibling;
                nextX->link(X);

            } else {
                if (prevX == nullptr)
                    head = nextX;
                else
                    prevX->sibling = nextX;

                X->link(nextX);
                X = nextX;
            }
            nextX = X->sibling;
        }
    }
    void insertBinominalHeap(T value){
        auto tree = new BinominalHeap<T>(value);
        unionBinominalHeap(this, tree);
        delete tree;
    }

    [[nodiscard]] Node* minValue(){
        Node* minimal = head;
        Node* temp    = head->sibling;

        while (temp != nullptr){
            if (temp->value < minimal->value)
                minimal = temp;
            temp = temp->sibling;
        }

        return minimal;
    }

};


#endif //LAB7_BINOMINALTREE__BINOMINALHEAP_H
