#include "Tree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
        tree.output();
    }
    tree.insert(-1);

    tree.output();
    return 0;
}
