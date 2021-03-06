#include "PersistentTree.h"

int main() {
    PersistentTree tree;
    for (int i = 0; i < 10; i += 2) {
        cout << "-------------------------INSERT " << i << "--------------------------------\n";
        tree.insert(i);
        tree.Dump();
    }

    tree.Dump();

    for (int i = 0; i < 10; i += 2){
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
