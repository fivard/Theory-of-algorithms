#include "Tree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 20; i++) {
        tree.insert(i);
        tree.output();
    }
    return 0;
}
