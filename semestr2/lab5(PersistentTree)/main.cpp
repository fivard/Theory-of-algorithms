#include "PersistentTree.h"

int main() {
<<<<<<< HEAD:semestr2/lab5(PersistentTree)/main.cpp
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

    //cout << "BACK UP TREE №8\n";
    tree.backUpPreviousRoot(tree.previousRoots[8]);
=======
    Tree tree;
    for (int i = 0; i < 16; i+=2) {
        //cout << "-------------------------" << i << "--------------------------------\n";
        tree.insert(i);
        //tree.Dump();
    }
>>>>>>> parent of d4ec7f6 ([ DONE ] deleting and backup):lab5(PersistentTree )/main.cpp
    tree.Dump();
    tree.DumpAllRoots();



    return 0;
}
