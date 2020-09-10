//
// Created by Admin on 10.09.2020.
//

#include "files.h"

void fillFileWithNumbers(int countOfNumbers){
    ofstream out;
    srand(rand());
    out.open("toSort.txt");
    vector<int> aLotOfNumbers;
    for (int i = 0; i < countOfNumbers-1; i++)
        out << rand()%500 << " ";
    out << rand()%500;
    out.close();
}

void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, const int sizeOfChunk, const int countOfFiles, const int countOfInputNumbers){
    int neededCountOfChunks = ceil(countOfInputNumbers/sizeOfChunk);
    int indexOfMaxFile = 0;
    int sizeOfMaxFile = 1;
    int countOfChunks = 0;

    countsOfChunkInEachFiles.push_back(1);
    for (int i = 0; i < countOfFiles-1; i++)
        countsOfChunkInEachFiles.push_back(0);

    while(countOfChunks < neededCountOfChunks){
        countOfChunks = 0;

        for(int i = 0; i < countsOfChunkInEachFiles.size(); i++)
            if (countsOfChunkInEachFiles[i] > countsOfChunkInEachFiles[indexOfMaxFile]) {
                indexOfMaxFile = i;
                sizeOfMaxFile = countsOfChunkInEachFiles[i];
            }

        for(int i = 0; i < countsOfChunkInEachFiles.size(); i++)
            if (i == indexOfMaxFile)
                countsOfChunkInEachFiles[i] = 0;
            else {
                countsOfChunkInEachFiles[i] += sizeOfMaxFile;
                countOfChunks += countsOfChunkInEachFiles[i];
            }
    }
}
