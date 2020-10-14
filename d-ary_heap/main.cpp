#include <iostream>
#include <vector>
#include <algorithm>

class dAryHeap{
    std::vector<int> heap;
    int countOfSons;


    int maxChild(int index){
        if (index*countOfSons + 1 >= heap.size())
            return 0;
        int sonIndex = index*countOfSons+1;
        int maxKey = heap[sonIndex];
        unsigned int last = (index+1)*countOfSons;
        if (last >= heap.size())
            last = heap.size()-1;
        for (int j = sonIndex + 1; j <= last; j++){
            if (maxKey < heap[j]){
                maxKey = heap[j];
                sonIndex = j;
            }
        }
        return sonIndex;

    }
    void surfacing(int index){ //O(log d n)
        int parentIndex = (index-1)/countOfSons;
        while (index != 0 && heap[parentIndex] < heap[index]){
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
            parentIndex = (index-1)/countOfSons;
        }
    }
    void dipping(int index){
        int sonIndex = maxChild(index);
        std::cout << sonIndex << '\n';
        while (sonIndex != 0 && heap[index] < heap[sonIndex]){
            std::swap(heap[index], heap[sonIndex]);
            index = sonIndex;
            sonIndex = maxChild(index);
        }
    }
public:
    explicit dAryHeap(int newCountOfSons){
        countOfSons = newCountOfSons;
        heap.clear();
    }
    void insert(int value){ // O(log d n)
        heap.push_back(value);
        surfacing(heap.size()-1);
    }
    int extractMax(){ // O(log d n)
        int maxValue = heap[0];
        std::swap(heap[0], heap[heap.size()-1]);
        heap.pop_back();
        dipping(0);
        return maxValue;
    }
    int increaseKey(int index, int value){ // O(log d n)
        heap[index] += value;
        surfacing(index);
    }
    void output(){
        for (int i : heap)
            std::cout << i << " ";
        std::cout << std::endl;
    } //TODO нормальный вывод
};

int main() {
    dAryHeap heap(5);
    for (int i = 0; i < 10; i++)
        heap.insert(i);
    heap.output();
    std::cout << heap.extractMax() << std::endl;

    heap.output();
    heap.increaseKey(5, 10);
    heap.output();
    heap.insert(1);
    heap.insert(10);
    heap.output();
    return 0;
}
