#include "PersistentTree.h"

int main() {
    PersistentTree tree;
    for (int i = 0; i < 16; i += 2)
        tree.insert(i);

    tree.Dump();

    for (int i = 0; i < 16; i += 2){
        cout << "-------------------------DELETING " << i << "--------------------------------\n";
        tree.erase(i);
        tree.Dump();
    }

    tree.DumpAllRoots();

    cout << "BACK UP TREE number 8\n";
    tree.backUpPreviousRoot(tree.previousRoots[8]);
    tree.Dump();



    return 0;
}
