#include <iostream>
#include "BinominalHeap.h"

int main() {
    BinominalHeap<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);
    tree.print();

    tree.extractMin();
    tree.print();

    tree.erase(tree.head->sibling->child->child->child);
    tree.print();
    return 0;
}
