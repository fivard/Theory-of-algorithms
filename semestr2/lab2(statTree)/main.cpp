#include "Tree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 20; i++) {
        tree.insert(i);
        tree.output();
    }
    tree.erase(12);
    tree.erase(14);
    tree.output();
    return 0;
}
