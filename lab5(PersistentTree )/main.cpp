#include "RedBlackTree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 16; i+=2) {
        //cout << "-------------------------" << i << "--------------------------------\n";
        tree.insert(i);
        //tree.Dump();
    }
    tree.Dump();
    tree.DumpAllRoots();



    return 0;
}
