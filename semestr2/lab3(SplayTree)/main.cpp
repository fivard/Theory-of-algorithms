#include <iostream>
#include <random>
#include "SplayTree.h"


int main() {
    SplayTree tree;

    vector<int> arr;
    arr.reserve(10);
    for (int i = 0; i < 10; i++)
        arr.push_back(i);

    shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));

    for(int i : arr){
        cout << "Wanted " << i << "...\n";
        tree.insert(i);
        std::cout << "-----------------------inserted" << i << "-----------------" << std::endl;
        tree.output();
    }

    for(int i = 0; i < 10; i++){
        std::cout << "-----------------------deleted" << i << "-----------------" << std::endl;
        tree.erase(i);
        tree.output();
    }

}