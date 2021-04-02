#include <iostream>
#include "BinominalHeap.h"

int main() {
    std::cout << "Print 1\n";
    BinominalHeap<int> tree(1);
    tree.printBinominalHeap();

    std::cout << "Print 2\n";
    tree.insertBinominalHeap(2);
    tree.printBinominalHeap();

    std::cout << "Print 3\n";
    tree.insertBinominalHeap(3);
    tree.printBinominalHeap();

    std::cout << "Print 4\n";
    tree.insertBinominalHeap(4);
    tree.printBinominalHeap();

    std::cout << "Print 5\n";
    tree.insertBinominalHeap(5);
    tree.printBinominalHeap();

    std::cout << "Print 6\n";
    tree.insertBinominalHeap(6);
    tree.printBinominalHeap();

    std::cout << "Print -1\n";
    tree.insertBinominalHeap(-1);
    tree.printBinominalHeap();

    std::cout << "Print -2\n";
    tree.insertBinominalHeap(-2);
    tree.printBinominalHeap();
    return 0;
}
