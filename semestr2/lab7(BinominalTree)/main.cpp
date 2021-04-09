#include <iostream>
#include "BinominalHeap.h"


int main() {
    BinominalHeap<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);
    std::cout << "NEW TREE\n";
    tree.print();

    std::cout << "EXTRACT MIN\n";
    tree.extractMin();
    tree.print();
    return 0;
}
