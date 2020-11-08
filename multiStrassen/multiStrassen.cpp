//
// Created by Admin on 08.11.2020.
//

#include <algorithm>

void outputMatrix(int** a, int row, int column){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            std::cout << a[i][j] << "\t";
        std::cout << std::endl;
    }
}

int log2(int x) {
    int result = 1;
    x--;
    while ((x >>= 1) != 0) result++;
    return result;
}

int getNewSize(int n1, int m, int n2){
    int _max = std::max({n1, m, n2});
    return 1 << log2(_max);
}

int** increaseSizeMatrix(int n, int** a, int currentRow, int currentColumn) {
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
        result[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < currentRow && j < currentColumn)
                result[i][j] = a[i][j];
            else
                result[i][j] = 0;
        }
    }

    return result;
}

void splitMatrix(int** a, int** a11, int** a12, int** a21, int** a22){
    
}