#include "RedBlackTree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 16; i += 2)
        tree.insert(i);

    tree.Dump();
    for (int i = 0; i < 16; i += 2){
        cout << "-------------------------DELETING " << i << "--------------------------------\n";
        tree.erase(i);
        tree.Dump();
    }

    tree.DumpAllRoots();

    tree.backUpPreviousRoot(tree.previousRoots[5]);
    tree.Dump();

    return 0;
}
