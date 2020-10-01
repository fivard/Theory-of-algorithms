#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;
void output(int left, int right, vector<int>& vec){
    for (int i = left; i <= right; i++)
        cout << vec[i] << " ";
    cout << endl;
}

int partition(vector<int> &array, int low, int high, int pivot) {
    int i = low;
    for (int j = low; j < high; j++){
        if (array[j] < pivot){
            swap(array[i], array[j]);
            i++;
        }
        else if (array[j] == pivot){
            swap(array[j], array[high]);
            j--;
        }
    }
    swap(array[i], array[high]);
    return i;

}

void doubleQuickSort(std::vector<int> &firstVector, std::vector<int> &secondVector, int low, int high) {
    if(high <= low)
        return;

    int pivot = partition(firstVector, low, high, secondVector[high]);
    partition(secondVector, low, high, firstVector[pivot]);
    doubleQuickSort(firstVector, secondVector, low, pivot - 1);
    doubleQuickSort(firstVector, secondVector, pivot + 1, high);

}
bool check(vector<int>& vec){
    for (int i = 1; i < vec.size(); i++)
        if (vec[i] < vec[i-1])
            return false;
    return true;
}

int main() {
    int n;
    cout << "Enter n\n";
    cin >> n;
    vector<int> firstVector(n), secondVector(n);
    for (int i = 0; i < n; i++)
        firstVector[i] = secondVector[n-i-1] = i;

    shuffle(firstVector.begin(), firstVector.end(), mt19937(random_device()()));
    shuffle(secondVector.begin(), secondVector.end(), mt19937(random_device()()));
    //output(0,n-1,firstVector);
    //output(0,n-1,secondVector);
    doubleQuickSort(firstVector, secondVector, 0, n-1);
    cout << "Sorted?\n";
    //output(0,n-1,firstVector);
    //output(0,n-1,secondVector);
    cout << check(firstVector) << " " << check(secondVector);
    return 0;
}
