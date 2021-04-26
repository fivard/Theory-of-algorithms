#include "BPlusTree.h"

int main() {
    BPlusTree<int, int> tree(3);
    for (int i = 0; i < 20; i++){
        std::cout << "-----------------------------------INSERT " << i << " ---------------------------\n";
        tree.insert(i, i);
        tree.print();
    }
    for (int i = 0; i < 20; i++){
        std::cout << "-----------------------------------ERASE " << i << " ----------------------------\n";
        tree.erase(i);
        tree.print();
    }
    return 0;
}
