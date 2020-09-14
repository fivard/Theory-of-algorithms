//
// Created by Admin on 10.09.2020.
//

#include <iostream>
#include "files.h"

void fillFileWithNumbers(const startData data){
    ofstream out;
    srand(time(NULL));
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

    for (int i = 0; i < data.countOfFiles; i++){
        File newFile;
        newFile.fileName = "file"+to_string(i)+".txt";

        //ofstream out(newFile.fileName, ios::binary);
        ofstream out(newFile.fileName);

        int newElement, j = 0;

        for (; j < countsOfChunksInEachFiles[i] && neededCountOfChunks > 0; j++){
            newFile.currentChunk.clear();

            for (int k = 0; k < data.sizeOfChunk && !in.eof(); k++) {
                in >> newElement;
                newFile.currentChunk.push_back(newElement);
            }

            neededCountOfChunks--;
            sort(newFile.currentChunk.begin(), newFile.currentChunk.end());

            for (auto number : newFile.currentChunk)
                out << number << " ";
                //out.write((char*)&number, sizeof(number));
        }
        if (neededCountOfChunks == 0)
            newFile.countOfChunks = j;
        else
            newFile.countOfChunks = countsOfChunksInEachFiles[i];

        files.push_back(newFile);
        out.close();
    }
}
string mergeSort(vector<File> &files){
    int indexOutputFile = 0;
    int indexMinFile = 0;
    string lastFile;

    vector<ifstream> ifstreams;
    for (int i = 0; i < files.size(); i++){
        ifstreams.push_back(ifstream {files[i].fileName});
    }

    while (!checkMergedAllFiles(files)) {
        for (int i = 0; i < files.size(); i++)
            files[i].inUse = false;

        indexOutputFile = getIndexOutputFile(files);
        indexMinFile = getIndexMinFile(files);


        cout << "\nCountOfChunks: ";
        for (int i = 0; i < files.size(); i++)
            cout << files[i].countOfChunks << " ";
        cout << endl << endl;

        mergeCurrentChunk(files, ifstreams, indexOutputFile);
        for (int i = 0; i < files[indexMinFile].countOfChunks-1; i++) {
            mergeCurrentChunkApp(files,ifstreams, indexOutputFile);
        }

        int minSize = files[indexMinFile].countOfChunks;
        for (int i = 0; i < files.size(); i++)
                if (files[i].countOfChunks > 0)
                    files[i].countOfChunks -= minSize;
        files[indexOutputFile].countOfChunks += minSize;

        lastFile = files[indexOutputFile].fileName;
    }
    cout << "\n\nSorted arrays is in " << lastFile << endl;

}
void mergeCurrentChunkApp(vector<File> &files, vector<ifstream> &ifstreams, const int indexOutputFile){
    //ofstream out(files[indexOutputFile].fileName, ios::binary);
    ifstreams[indexOutputFile].close();
    ofstream out(files[indexOutputFile].fileName, ios::app);
    
    for (int i = 0; i < files.size(); i++)
        if (files[i].countOfChunks > 0)
            files[i].inUse = true;

    int indexMinNumber = 0, tempNumber;

    vector<int> currentNumbers;
    for (int i = 0; i < files.size(); i++) {
        if (files[i].inUse) {
            ifstreams[i] >> tempNumber;
            currentNumbers.push_back(tempNumber);
            if (currentNumbers[indexMinNumber] > tempNumber)
                indexMinNumber = i;
        }else{
            currentNumbers.push_back(1000);
        }
    }
    //cout << currentNumbers[indexMinNumber] << " ";
    out << currentNumbers[indexMinNumber] << " ";

    while(!checkMergedCurrentChunk(files)){
        if (!files[indexMinNumber].inUse)
            for (int i = 0; i < files.size(); i++)
                if (files[i].inUse)
                    indexMinNumber = i;

        int pos = ifstreams[indexMinNumber].tellg();
        if (!(ifstreams[indexMinNumber] >> tempNumber) || tempNumber < currentNumbers[indexMinNumber]) {
            files[indexMinNumber].inUse = false;
            currentNumbers[indexMinNumber] = 1000;
            ifstreams[indexMinNumber].seekg(pos);
        } else
            currentNumbers[indexMinNumber] = tempNumber;

        for (int i = 0; i < files.size(); i++){
            if (files[i].inUse){
                if (currentNumbers[i] < currentNumbers[indexMinNumber])
                    indexMinNumber = i;
            }
        }

        if (!checkMergedCurrentChunk(files)) {
            out << currentNumbers[indexMinNumber] << " ";
            //cout << currentNumbers[indexMinNumber] << " ";
        }
    }
    out.close();
    ifstreams[indexOutputFile].open(files[indexOutputFile].fileName);
}
void mergeCurrentChunk(vector<File> &files, vector<ifstream> &ifstreams, const int indexOutputFile){
    //ofstream out(files[indexOutputFile].fileName, ios::binary);
    ifstreams[indexOutputFile].close();
    ofstream out(files[indexOutputFile].fileName);

    for (int i = 0; i < files.size(); i++)
        if (files[i].countOfChunks > 0)
            files[i].inUse = true;

    int indexMinNumber = 0, tempNumber;

    vector<int> currentNumbers;
    for (int i = 0; i < files.size(); i++) {
        if (files[i].inUse) {
            ifstreams[i] >> tempNumber;
            currentNumbers.push_back(tempNumber);
            if (currentNumbers[indexMinNumber] > tempNumber)
                indexMinNumber = i;
        }else{
            currentNumbers.push_back(1000);
        }
    }
    //cout << currentNumbers[indexMinNumber] << " ";
    out << currentNumbers[indexMinNumber] << " ";

    while(!checkMergedCurrentChunk(files)){
        if (!files[indexMinNumber].inUse)
            for (int i = 0; i < files.size(); i++)
                if (files[i].inUse)
                    indexMinNumber = i;

        int pos = ifstreams[indexMinNumber].tellg();
        if (!(ifstreams[indexMinNumber] >> tempNumber) || tempNumber < currentNumbers[indexMinNumber]) {
            files[indexMinNumber].inUse = false;
            currentNumbers[indexMinNumber] = 1000;
            ifstreams[indexMinNumber].seekg(pos);
        } else
            currentNumbers[indexMinNumber] = tempNumber;

        for (int i = 0; i < files.size(); i++){
            if (files[i].inUse){
                if (currentNumbers[i] < currentNumbers[indexMinNumber])
                    indexMinNumber = i;
            }
        }

        if (!checkMergedCurrentChunk(files)) {
            out << currentNumbers[indexMinNumber] << " ";
            //cout << currentNumbers[indexMinNumber] << " ";
        }
    }
    out.close();
    ifstreams[indexOutputFile].open(files[indexOutputFile].fileName);
}
int getIndexOutputFile(vector<File> &files) {
    int indexOutputFile = 0;
    bool flag = false;
    for (int i = 0; i < files.size() && !flag; i++)
        if (files[i].countOfChunks == 0) {
            indexOutputFile = i;
            flag = true;
        }
    return indexOutputFile;
}
int getIndexMinFile(vector<File> &files){
    int indexMinFile = 0;
    while(files[indexMinFile].countOfChunks == 0)
        indexMinFile++;

    for (int i = 0; i < files.size(); i++)
        if (files[i].countOfChunks < files[indexMinFile].countOfChunks && files[i].countOfChunks > 0)
            indexMinFile = i;

    return indexMinFile;
}
bool checkMergedAllFiles(vector<File> &files){
    int sumChunks = 0;
    for (int i = 0; i < files.size(); i++)
        sumChunks += files[i].countOfChunks;

    return sumChunks == 1;
}
bool checkMergedCurrentChunk(vector<File> &files){
    for (int i = 0; i < files.size(); i++)
        if (files[i].inUse)
            return false;

    return true;
}

