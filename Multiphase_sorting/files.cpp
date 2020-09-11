//
// Created by Admin on 10.09.2020.
//

#include "files.h"

void fillFileWithNumbers(const startData data){
    ofstream out;
    srand(rand());
    out.open("toSort.txt");
    vector<int> aLotOfNumbers;
    for (int i = 0; i < data.countOfInputNumbers-1; i++)
        out << rand()%500 << " ";
    out << rand()%500;
    out.close();
}

void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, const startData data){
    int indexOfMaxFile = 0;
    int sizeOfMaxFile = 1;
    int countOfChunks = 0;

    countsOfChunkInEachFiles.push_back(1);
    for (int i = 0; i < data.countOfFiles-1; i++)
        countsOfChunkInEachFiles.push_back(0);

    while(countOfChunks < data.neededCountOfChunks){
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

void setFilesNameAndCountsOfChunks(vector<File> &files, const startData data, vector<int> countsOfChunksInEachFiles){
    ifstream in("toSort.txt");

    int neededCountOfChunks = data.neededCountOfChunks;

    for (int i = 1; i <= data.countOfFiles; i++){
        ofstream out("file"+to_string(i)+".txt");
        File newFile;
        newFile.docSize = countsOfChunksInEachFiles[i-1];
        newFile.fileName = "file"+to_string(i)+".txt";

        int newElement, j = 0;
        for (; j < newFile.docSize && neededCountOfChunks > 0; j++){
            newFile.currentChunk.clear();
            for (int k = 0; k < data.sizeOfChunk && !in.eof(); k++) {
                in >> newElement;
                newFile.currentChunk.push_back(newElement);
            }
            neededCountOfChunks--;
            sort(newFile.currentChunk.begin(), newFile.currentChunk.end());
            for (auto number : newFile.currentChunk)
                out << number << " ";
            out << "|" << " ";
        }
        if (neededCountOfChunks == 0)
            newFile.factSize = j;
        else
            newFile.factSize = newFile.docSize;

        files.push_back(newFile);
        out.close();
    }
}