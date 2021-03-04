#include "OptimalBinaryTree.h"

int main() {
    double keys[6]           = {0   , 0.15, 0.10, 0.05, 0.10, 0.20};
    double fictitiousKeys[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    OptimalBinaryTree tree(5, keys, fictitiousKeys);
    return 0;
}
