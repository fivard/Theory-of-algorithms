#include "OptimalBinaryTree.h"

int main() {
    double keys1[6]           = {0   , 0.15, 0.10, 0.05, 0.10, 0.20};
    double fictitiousKeys1[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    OptimalBinaryTree tree1(5, keys1, fictitiousKeys1);
    tree1.output();

    double keys2[8]           = {0   , 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    double fictitiousKeys2[8] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};

    OptimalBinaryTree tree2(7, keys2, fictitiousKeys2);
    tree2.output();

    return 0;
}
