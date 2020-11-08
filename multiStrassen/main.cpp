#include <iostream>
#include <ctime>
#include "multiStrassen.cpp"

void generateMatrix(int** a, const int& row, const int& column){
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            a[i][j] = rand() % 10;

}


int main() {
    srand(time(nullptr));
    int n1, m, n2;
    std::cout << "Enter size of first matrix [n1]*[m]\n";
    std::cout << "Enter n1: ";
    std::cin >> n1;
    std::cout << "\nEnter m: ";
    std::cin >> m;
    std::cout << "\nEnter size of second matrix [m]*[n2]\n";
    std::cout << "\nEnter n2: ";
    std::cin >> n2;
    int** a, **b;
    a = new int*[n1];
    for (int i = 0; i < n1; i++)
        a[i] = new int[m];
    b = new int*[m];
    for (int i = 0; i < m; i++)
        b[i] = new int[n2];

    generateMatrix(a, n1, m);
    generateMatrix(b, m, n2);

    double start = clock();
    int** c1 = multiplyMatrix(a, b, n1, m, n2);
    double end = clock();
    double time  = (end - start) / CLOCKS_PER_SEC;
    std::cout << "\nTime for multiply USUAL matrix " << time << '\n';
    //outputMatrix(c1, n1, n2);

    int n = getNewSize(n1, m, n2);
    a = increaseSizeMatrix(n, a, n1, m);
    b = increaseSizeMatrix(n, b, m, n2);

    start = clock();
    int** c2 = multiplyStrassen(a, b, n);
    end = clock();
    time = (end - start) / CLOCKS_PER_SEC;
    std::cout << "\nTime for multiply STRASSEN matrix " << time << '\n';
    //outputMatrix(c2, n, n);

    if (compareMatrix(c1, c2, n1, n2))
        std::cout << "Algorithm works\n";
    else
        std::cout << "Algorithm doesn't work\n";


    for (int i = 0; i < n; i++)
        delete b[i];
    delete[] b;
    for (int i = 0; i < n; i++)
        delete a[i];
    delete[] a;
    for (int i = 0; i < n1; i++)
        delete c1[i];
    delete[] c1;
    for (int i = 0; i < n; i++)
        delete c2[i];
    delete[] c2;
    return 0;
}
