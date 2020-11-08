#include <iostream>
#include <ctime>
#include "multiStrassen.cpp"

void generateMatrix(int** a, const int& row, const int& column){
    srand(time(nullptr));

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            a[i][j] = rand();

}


int main() {
    int n1, m, n2;
    std::cout << "Enter size of first matrix [n1]*[m]\n";
    std::cout << "Enter n1: \n";
    std::cin >> n1;
    std::cout << "Enter m: \n";
    std::cin >> m;
    std::cout << "Enter size of second matrix [m]*[n2]\n";
    std::cout << "Enter n2: \n";
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

    outputMatrix(a, n1, m);
    std::cout << std::endl;
    outputMatrix(b, m, n2);

    int n = getNewSize(n1, m, n2);
    std::cout << n;
    a = increaseSizeMatrix(n, a, n1, m);
    b = increaseSizeMatrix(n, b, m, n2);

    outputMatrix(a, n, n);
    std::cout << std::endl;
    outputMatrix(b, n, n);

    for (int i = 0; i < n; i++)
        delete b[i];
    delete b;
    for (int i = 0; i < n; i++)
        delete a[i];
    delete a;
    return 0;
}
