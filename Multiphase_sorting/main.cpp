#include <iostream>
#include <string>
#include "files.h"

class File{
    string fileName;
    int factSize;
    int docSize;
    vector<int> currentChunk;
};

void outputVec(vector<int> vec);
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles);

int main() {

    int countOfInputNumbers;
    int countOfFiles;
    int sizeOfChunk;

    cout << "Enter a count of the input numbers\n";
    cin >> countOfInputNumbers;
    cout << "Enter a count of the files\n";
    cin >> countOfFiles;
    cout << "Enter size of a chunk\n";
    cin >> sizeOfChunk;

    vector<int> countsOfChunksInEachFiles;
    countSizeOfFiles(countsOfChunksInEachFiles, sizeOfChunk, countOfFiles, countOfInputNumbers);

    fillFileWithNumbers(countOfInputNumbers);

    return 0;
}



void outputVec(vector<int> vec){
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}

