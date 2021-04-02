#include <iostream>
#include "BinominalHeap.h"

int main() {
    BinominalHeap<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insertBinominalHeap(i);
    tree.printBinominalHeap();

    tree.extractMinBinominalHeap();
    tree.printBinominalHeap();
    return 0;
}
