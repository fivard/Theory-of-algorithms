#include <iostream>
#include <ctime>

class element{
public:
    int value;
    bool key;
};

void generatingArray(int n, element array[]){
    for (std::size_t i = 0; i < n; i++){
        array[i].value = rand();
        array[i].key = rand() % 2;
    }
}

void outputArray(int n, element array[]){
    for (int i = 0; i < n; i++)
        std::cout << array[i].value << " ";
    std::cout << "\n";
    for (int i = 0; i < n; i++)
        std::cout << array[i].key << " ";
    std::cout << "\n";
}

//O(n) - time, O(n) - memory, stable
void indexSort(int n, element array[]){
    int countOfZero = 0, countOfOne;
    for (int i = 0; i < n; i++)
        if (array[i].key == 0)
            countOfZero++;

    countOfOne = n - countOfZero;
    int* arrayForZero = new int[countOfZero];
    int* arrayForOne = new int[countOfOne];

    int indexForZero = 0, indexForOne = 0;
    for (int i = 0; i < n; i++){
        if (array[i].key == 0)
            arrayForZero[indexForZero++] = i;
        else
            arrayForOne[indexForOne++] = i;
    }

    auto* newArray = new element[n];
    for (int i = 0; i < countOfZero; i++)
        newArray[i] = array[arrayForZero[i]];

    for (int i = 0; i < countOfOne; i++)
        newArray[countOfZero + i] = array[arrayForOne[i]];

    for (int i = 0; i < n; i++)
        array[i] = newArray[i];
}

//O(n) - time, O(1) - memory, unstable
void quickSort(int n, element array[]){
    int i = 0, j = n-1;
    while (i < n && j >=0 && i < j){
        while(array[i].key == 0 && i < n)
            i++;
        while(array[j].key == 1 && j >= 0)
            j--;

        if (i < j){
            element temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        i++;
        j--;
    }

}

//O(n^2) - time, O(1) 0 memory, stable
void  insertionSort(int n, element array[]){
    int j;
    element current;
    for (int i = 1; i < n; i++){
        current = array[i];
        j = i - 1;
        while(j >= 0 && array[j].key > current.key)
            array[j + 1] = array[j--];

        array[j + 1] = current;
    }
}

bool checkSorted(int n, element array[]){
    for (int i = 1; i < n; i++)
        if (array[i].key < array[i-1].key)
            return  false;
    return true;
}

double checkTime(int n, element array[], void (*sortFunction)(int, element[])){
    double start = clock();
    sortFunction(n, array);
    double end = clock();
    return (end - start) / CLOCKS_PER_SEC;
}

int main() {
    int n;
    std::cout << "Enter a size\n";
    std::cin >> n;
    element array[n];

    void (*index)(int, element[]) = indexSort;
    void (*quick)(int, element[]) = quickSort;
    void (*insertion)(int, element[]) = insertionSort;

    std::cout << "\nadditional memory sort:\n";
    generatingArray(n, array);
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;
    std::cout << "Time = " << checkTime(n, array, index) << std::endl;
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;

    std::cout << "\nunstable sort:\n";
    generatingArray(n, array);
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;
    std::cout << "Time = " << checkTime(n, array, quick) << std::endl;
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;

    std::cout << "\nadditional time:\n";
    generatingArray(n, array);
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;
    std::cout << "Time = " << checkTime(n, array, insertion) << std::endl;
    //outputArray(n, array);
    std::cout << "Sorted: " << checkSorted(n, array) << std::endl;
    return 0;
}
