#include "FibonacciHeap.h"

int main() {
    FibonacciHeap<int> heap;
    Node<int> *temp, *node1, *node2, *node3, *node4;
    std::cout << "INSERT 15 NODES\n\n";
    for (int i = 0; i < 20; i++) {
        temp = heap.insert(i + 1);
        if (i == 8)
            node1 = temp;
        if (i == 7)
            node3 = temp;
        if (i == 6)
            node2 = temp;
        if (i == 11)
            node4 = temp;
    }
    heap.print();
    for (int i = 0; i < 20; i++){
        heap.extractMin();
        heap.print();
    }

    std::cout << "\n\nEXTRACT MIN\n\n";

//    std::cout << "\n\nDECREASE 9 to 1\n\n";
//    heap.decreaseKey(node1, 1);
//    heap.print();
//
//    std::cout << "\n\nDECREASE 7 to 0\n\n";
//    heap.decreaseKey(node2, 0);
//    heap.print();
//
//    std::cout << "\n\nDECREASE 8 to -1\n\n";
//    heap.decreaseKey(node3, -1);
//    heap.print();
//
//    std::cout << "\n\nEXTRACT MIN\n\n";
//    heap.extractMin();
//    heap.print();
//
//    std::cout << "\n\nDELETE 12\n\n";
//    heap.deleteNode(node4);
//    heap.print();

    return 0;
}
