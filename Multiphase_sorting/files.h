//
// Created by Admin on 10.09.2020.
//

#ifndef MULTIPHASE_SORTING_FILES_H
#define MULTIPHASE_SORTING_FILES_H

#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class startData{
public:
    int countOfInputNumbers;
    int countOfFiles;
    int sizeOfChunk;
    int neededCountOfChunks;
};

class File{
public:
    string fileName;
    int factSize;
    int docSize;
    vector<int> currentChunk;
};

using namespace std;

void fillFileWithNumbers(const startData data);
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, const startData data);

void setFilesNameAndCountsOfChunks(vector<File> &files, const startData data, vector<int> countsOfChunksInEachFiles);

#endif //MULTIPHASE_SORTING_FILES_H
