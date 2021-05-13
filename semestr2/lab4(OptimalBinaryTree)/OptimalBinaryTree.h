//
// Created by Acer on 04.03.2021.
//

#ifndef OPTIMALBINARYTREE_LAB4_OPTIMALBINARYTREE_H
#define OPTIMALBINARYTREE_LAB4_OPTIMALBINARYTREE_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class OptimalBinaryTree{
private:

    class Node {
    public:
        int     value;
        double  probability;
        bool    mainKey;

        Node    *parent;
        Node    *left;
        Node    *right;

                 Node() {
            left = right = parent = nullptr;
        }
        explicit Node(int value, double probability, bool mainKey){
            this->value = value;
            this->probability = probability;
            this->mainKey = mainKey;
            left = right = parent = nullptr;
        }
                ~Node() = default;

        void output(Node *node, int space) const {
            if (node == nullptr)
                return;

            space += 10;

            output(node->right, space);

            cout << endl;
            for (int i = 10; i < space; i++)
                cout << " ";
            cout << node->value << ":" << node->probability << "\n";
            output(node->left, space);
        }
    };

    Node     *root;
    int      countKeys;

    double*  keys;
    double*  fictitiousKeys;

    double** expectedValue;
    int**    roots;

    void generateTables(){
        double weights[countKeys + 2][countKeys+1];

        for (int i = 0; i < countKeys + 2; i++)
            for (int j = 0; j < countKeys + 1; j++)
                weights[i][j] = 0;
        for (int i = 1; i <= countKeys + 1; i++){
            expectedValue[i][i-1] = fictitiousKeys[i-1];
            weights[i][i-1]       = fictitiousKeys[i-1];
        }
        for (int k = 1; k <= countKeys; k++){
            for (int i = 1; i <= countKeys - k + 1; i++){
                int j               = i + k - 1;
                expectedValue[i][j] = 1000;
                weights[i][j]       = weights[i][j-1] + keys[j] + fictitiousKeys[j];

                for (int r = i; r <= j; r++){
                    double t = expectedValue[i][r-1] +
                                expectedValue[r+1][j] +
                                weights[i][j];
                    if (t < expectedValue[i][j]){
                        expectedValue[i][j] = t;
                        roots[i][j]         = r;
                    }
                }
            }
        }
        cout << "weights:\n";
        for (int i = 1; i <= countKeys+1; i++) {
            for (int j = 0; j <= countKeys; j++)
                cout << weights[i][j] << '\t';
            cout << endl;
        }
        cout << endl;
        cout << "roots:\n";
        for (int i = 1; i <= countKeys; i++) {
            for (int j = 1; j <= countKeys; j++)
                cout << roots[i][j] << '\t';
            cout << endl;
        }
        cout << endl;
        cout << "expected value:\n";
        for (int i = 1; i <= countKeys+1; i++) {
            for (int j = 0; j <= countKeys; j++)
                cout << expectedValue[i][j] << '\t';
            cout << endl;
        }
    };
    [[ nodiscard ]] Node* generateTree(int i, int j, Node* parent){
        if (j == i - 1){
            return new Node(0, fictitiousKeys[i-1], false);
        }

        int currentNode = roots[i][j];
        Node *node = new Node(currentNode, keys[ currentNode ], true);
        node->parent = parent;
        node->left = generateTree(i, currentNode - 1, node);
        node->right = generateTree( currentNode + 1, j, node);

        return node;
    };
public:
    OptimalBinaryTree(const int count, const double* newKeys, const double* newFictitiousKeys){
        root      = nullptr;
        countKeys = count;

        keys = new double [countKeys + 1];
        for (int i = 0; i <= count; i++)
            keys[i] = newKeys[i];

        fictitiousKeys = new double [countKeys + 1];
        for (int i = 0; i <= count; i++)
            fictitiousKeys[i] = newFictitiousKeys[i];

        expectedValue = new double* [count + 2];
        for (int i = 1; i < count + 2; i++)
            expectedValue[i] = new double [count+1];

        roots = new int* [count + 1];
        for (int i = 1; i < count + 1; i++)
            roots[i] = new int [count + 1];

        for (int i = 1; i <= countKeys; i++)
            for (int j = 1; j <= countKeys; j++)
                roots[i][j] = 0;

        for (int i = 1; i <= countKeys+1; i++)
            for (int j = 0; j <= countKeys; j++)
                expectedValue[i][j] = 0;

        generateTables();
        root = generateTree(1, countKeys, nullptr);
    }
    ~OptimalBinaryTree(){
        delete keys;
        delete fictitiousKeys;

        for (int i = 1; i < countKeys + 2; i++)
            delete expectedValue[i];
        delete expectedValue;

        for (int i = 1; i < countKeys + 1; i++)
            delete roots[i];
        delete roots;
    }

    void output() const {
        cout << "\nTree:\n";
        root->output(root, 0);
    }
};

#endif //OPTIMALBINARYTREE_LAB4_OPTIMALBINARYTREE_H
