#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int countOfInputNumbers;
int countOfFiles;
int sizeOfChunk;

class File{
    string fileName;
    int factSize;
    int docSize;
};

void outputVec(vector<int> vec){
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}

void countSizeOFChunks(vector<int> &sizesOfFile){
    int neededCountOfChunks = ceil(countOfInputNumbers/sizeOfChunk);
    int indexOfMaxFile = 0;
    int sizeOfMaxFile = 1;
    int countOfChunks = 0;

    sizesOfFile.push_back(1);
    for (int i = 0; i < countOfFiles-1; i++)
        sizesOfFile.push_back(0);

    while(countOfChunks < neededCountOfChunks){
        countOfChunks = 0;

        for(int i = 0; i < sizesOfFile.size(); i++)
            if (sizesOfFile[i] > sizesOfFile[indexOfMaxFile]) {
                indexOfMaxFile = i;
                sizeOfMaxFile = sizesOfFile[i];
            }

        for(int i = 0; i < sizesOfFile.size(); i++)
            if (i == indexOfMaxFile)
                sizesOfFile[i] = 0;
            else {
                sizesOfFile[i] += sizeOfMaxFile;
                countOfChunks += sizesOfFile[i];
            }

        cout << countOfChunks << endl;
        outputVec(sizesOfFile);
    }
}

int main() {
    cout << "Enter a count of the input numbers\n";
    cin >> countOfInputNumbers;
    cout << "Enter a count of the files\n";
    cin >> countOfFiles;
    cout << "Enter size of a chunk\n";
    cin >> sizeOfChunk;
    vector<int> sizesOfChunks;
    countSizeOFChunks(sizesOfChunks);

    return 0;
}
