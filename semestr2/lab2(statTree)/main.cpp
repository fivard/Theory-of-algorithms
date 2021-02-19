#include "Tree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 13; i++)
        tree.insert(i);
    tree.Dump();

    for (int i = 0; i < 13; i++) {
        tree.erase(i);
        cout << "-----------------------------DELETE ";
        cout << i;
        cout << "-----------------------------\n";
        tree.Dump();
    }
    return 0;
}
