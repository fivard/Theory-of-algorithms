#include "Tree.h"

int main() {
    Tree tree;
    for (int i = 0; i < 20; i++)
        tree.insert(i);

    for (int i = 0; i < 19; i++) {
        tree.erase(i);
        tree.output();
    }
    return 0;
}
