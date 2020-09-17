#include <iostream>
#include <string>
#include "files.h"

int main() {
    startData data{};
    cout << "Enter a count of the input numbers: ";
    cin >> data.countOfInputNumbers;
    cout << "\nEnter a count of the files: ";
    cin >> data.countOfFiles;
    cout << "\nEnter size of a chunk: ";
    cin >> data.sizeOfChunk;
    cout << endl;

    data.neededCountOfChunks = ceil(data.countOfInputNumbers/(double)data.sizeOfChunk);

    vector<int> countsOfChunksInEachFiles;
    vector<File> files;

    countSizeOfFiles(countsOfChunksInEachFiles, data);
    fillFileWithNumbers(data);
    setFilesNameAndCountsOfChunks(files, data, countsOfChunksInEachFiles);
    mergeSort(files);

    return 0;
}
