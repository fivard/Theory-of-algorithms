//
// Created by Admin on 10.09.2020.
//

#ifndef MULTIPHASE_SORTING_FILES_H
#define MULTIPHASE_SORTING_FILES_H

#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void fillFileWithNumbers(int countOfNumbers);
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, const int sizeOfChunk, const int countOfFiles, const int countOfInputNumbers);

#endif //MULTIPHASE_SORTING_FILES_H
