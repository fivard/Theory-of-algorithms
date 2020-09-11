#include <iostream>
#include <string>
#include "files.h"


void outputVec(vector<int> vec);
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles);

int main() {
    startData data{};
    cout << "Enter a count of the input numbers\n";
    cin >> data.countOfInputNumbers;
    cout << "Enter a count of the files\n";
    cin >> data.countOfFiles;
    cout << "Enter size of a chunk\n";
    cin >> data.sizeOfChunk;

    data.neededCountOfChunks = ceil(data.countOfInputNumbers/(double)data.sizeOfChunk);

    vector<int> countsOfChunksInEachFiles;
    vector<File> files;
    countSizeOfFiles(countsOfChunksInEachFiles, data);

    cout << data.neededCountOfChunks << endl;
    outputVec(countsOfChunksInEachFiles);

    fillFileWithNumbers(data);
    setFilesNameAndCountsOfChunks(files, data, countsOfChunksInEachFiles);


    return 0;
}



void outputVec(vector<int> vec){
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}

