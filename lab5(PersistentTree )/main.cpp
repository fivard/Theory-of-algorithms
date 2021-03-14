#include "RedBlackTree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 13; i++)
        tree.insert(i);
    tree.Dump();

    return 0;
}
