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

void splitMatrix(int** a,int n, int** a11, int** a12, int** a21, int** a22){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a11[i][j] = a[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a12[i][j] = a[i][j + n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a21[i][j] = a[i + n][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a22[i][j] = a[i + n][j + n];
}

int** collectMatrix(int n, int** a11, int** a12, int** a21, int** a22){
    int** result = new int* [n*2];
    for (int i = 0; i < n*2; i++)
        result[i] = new int[n*2];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = a11[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j + n] = a12[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i + n][j] = a21[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i + n][j + n] = a22[i][j];

    return result;
}

int** summationMatrix(int** a, int** b, int n){
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
        result[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = a[i][j] + b[i][j];

    return  result;
}

int** subtractionMatrix(int** a, int** b, int n){
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
        result[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = a[i][j] - b[i][j];

    return  result;
}

int** multiplyMatrix(int** a, int** b, int n1, int m, int n2){
    int** result = new int*[n1];
    for (int i = 0; i < n1; i++)
        result[i] = new int[n2];

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            result[i][j] = 0;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

int** multiplyStrassen(int** a, int** b, int n) {
    if (n <= 512) {
        return multiplyMatrix(a, b, n, n ,n);
    }

    n = n >> 1;

    int** a11 = new int*[n];
    for (int i = 0; i < n; i++)
        a11[i] = new int[n];

    int** a12 = new int*[n];
    for (int i = 0; i < n; i++)
        a12[i] = new int[n];

    int** a21 = new int*[n];
    for (int i = 0; i < n; i++)
        a21[i] = new int[n];

    int** a22 = new int*[n];
    for (int i = 0; i < n; i++)
        a22[i] = new int[n];

    int** b11 = new int*[n];
    for (int i = 0; i < n; i++)
        b11[i] = new int[n];

    int** b12 = new int*[n];
    for (int i = 0; i < n; i++)
        b12[i] = new int[n];

    int** b21 = new int*[n];
    for (int i = 0; i < n; i++)
        b21[i] = new int[n];

    int** b22 = new int*[n];
    for (int i = 0; i < n; i++)
        b22[i] = new int[n];

    splitMatrix(a,n, a11, a12, a21, a22);
    splitMatrix(b,n, b11, b12, b21, b22);

    ///counting p
    int** p1 = multiplyStrassen(summationMatrix(a11, a22, n), summationMatrix(b11, b22, n), n);
    int** p2 = multiplyStrassen(summationMatrix(a21, a22, n), b11, n);
    int** p3 = multiplyStrassen(a11, subtractionMatrix(b12, b22, n), n);
    int** p4 = multiplyStrassen(a22, subtractionMatrix(b21, b11, n), n);
    int** p5 = multiplyStrassen(summationMatrix(a11, a12, n), b22, n);
    int** p6 = multiplyStrassen(subtractionMatrix(a21, a11, n), summationMatrix(b11, b12, n), n);
    int** p7 = multiplyStrassen(subtractionMatrix(a12, a22, n), summationMatrix(b21, b22, n), n);

    /// counting sub matrix c
    int** c11 = summationMatrix(summationMatrix(p1, p4, n), subtractionMatrix(p7, p5, n), n);
    int** c12 = summationMatrix(p3, p5, n);
    int** c21 = summationMatrix(p2, p4, n);
    int** c22 = summationMatrix(subtractionMatrix(p1, p2, n), summationMatrix(p3, p6, n), n);

    ///delete sub matrix a
    for (int i = 0; i < n; i++)
        delete a11[i];
    delete[] a11;
    for (int i = 0; i < n; i++)
        delete a12[i];
    delete[] a12;
    for (int i = 0; i < n; i++)
        delete a21[i];
    delete[] a21;
    for (int i = 0; i < n; i++)
        delete a22[i];
    delete[] a22;
    for (int i = 0; i < n; i++)
        delete b11[i];
    /// delete sub matrix b
    delete[] b11;
    for (int i = 0; i < n; i++)
        delete b12[i];
    delete[] b12;
    for (int i = 0; i < n; i++)
        delete b21[i];
    delete[] b21;
    for (int i = 0; i < n; i++)
        delete b22[i];
    delete[] b22;
    /// delete all p
    for (int i = 0; i < n; i++)
        delete p1[i];
    delete[] p1;
    for (int i = 0; i < n; i++)
        delete p2[i];
    delete[] p2;
    for (int i = 0; i < n; i++)
        delete p3[i];
    delete[] p3;
    for (int i = 0; i < n; i++)
        delete p4[i];
    delete[] p4;
    for (int i = 0; i < n; i++)
        delete p5[i];
    delete[] p5;
    for (int i = 0; i < n; i++)
        delete p6[i];
    delete[] p6;
    for (int i = 0; i < n; i++)
        delete p7[i];
    delete[] p7;

    return collectMatrix(n, c11, c12, c21, c22);
}

bool compareMatrix(int** c1, int** c2, int row, int column){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            if (c1[i][j] != c2[i][j])
                return false;
    }
    return  true;
}