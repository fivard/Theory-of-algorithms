//
// Created by Admin on 10.09.2020.
//

#include <iostream>
#include "files.h"

void fillFileWithNumbers(const startData data){
    ofstream out;
    srand(time(NULL));
    out.open("toSort.bin", ios::binary);
    vector<int> aLotOfNumbers;
    int randNumber;
    for (int i = 0; i < data.countOfInputNumbers-1; i++) {
        randNumber = rand()%1000;
        out.write((char *)&randNumber, sizeof(randNumber));
    }

    randNumber = rand()%1000;
    out.write((char *)&randNumber, sizeof(randNumber));

    out.close();
}
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, startData &data){
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
    data.sizeOfChunk = data.countOfInputNumbers / countOfChunks;
    data.neededCountOfChunks = countOfChunks;
}
void setFilesNameAndCountsOfChunks(vector<File> &files, const startData &data, vector<int> countsOfChunksInEachFiles){
    ifstream in("toSort.bin", ios::binary);

    int neededCountOfChunks = data.neededCountOfChunks;

    for (int i = 0; i < data.countOfFiles; i++){
        File newFile;
        newFile.fileName = "file"+to_string(i)+".bin";

        ofstream out(newFile.fileName, ios::binary);

        int newElement, j = 0;
        for (; j < countsOfChunksInEachFiles[i] && neededCountOfChunks > 0; j++){
            newFile.currentChunk.clear();

            for (int k = 0; k < data.sizeOfChunk && !in.eof(); k++) {
                in.read((char *)&newElement, sizeof(int));
                newFile.currentChunk.push_back(newElement);
            }

            neededCountOfChunks--;
            sort(newFile.currentChunk.begin(), newFile.currentChunk.end());
            for (auto number : newFile.currentChunk) {
                out.write((char *) &number, sizeof(number));
            }
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
    string lastFile = "file0.bin";

    vector<ifstream> ifstreams;
    for (int i = 0; i < files.size(); i++){
        ifstreams.push_back(ifstream {files[i].fileName, ios::binary});
    }

    double timePushStart = clock();
    while (!checkMergedAllFiles(files)) {
        for (int i = 0; i < files.size(); i++)
            files[i].inUse = false;

        indexOutputFile = getIndexOutputFile(files);
        indexMinFile = getIndexMinFile(files);

        cout << "\nCountOfChunks: ";
        for (int i = 0; i < files.size(); i++)
            cout << files[i].countOfChunks << " ";
        cout << endl;

        int minSize = files[indexMinFile].countOfChunks;

        ifstreams[indexOutputFile].close();
        ofstream out(files[indexOutputFile].fileName, ios::binary);

        for (int i = 0; i < files[indexMinFile].countOfChunks; i++) {
            mergeCurrentChunk(files, ifstreams, out, indexOutputFile);
        }
        for (int i = 0; i < files.size(); i++)
            if (files[i].countOfChunks > 0)
                files[i].countOfChunks -= minSize;
        files[indexOutputFile].countOfChunks += minSize;

        out.close();
        ifstreams[indexOutputFile].open(files[indexOutputFile].fileName, ios::binary);

        lastFile = files[indexOutputFile].fileName;
    }

    for (int i = 0; i < files.size(); i++)
        ifstreams[i].close();

    cout << "\n\nSorted arrays is in " << lastFile << endl;

    double timePushEnd = clock();
    double timePush = (timePushEnd - timePushStart) / CLOCKS_PER_SEC;

    cout << "\n end sort " << timePush << endl;

    /*ifstream in(lastFile, ios::binary);
    int val;
    in.seekg(0, ios::end);
    int end_file = in.tellg();
    in.seekg(0, ios::beg);
    while (in.tellg() != end_file){
        in.read((char *)&val, sizeof(int));
        cout << val << " ";
    }
    in.close();*/
}
void mergeCurrentChunk(vector<File> &files, vector<ifstream> &ifstreams, ofstream &out, const int indexOutputFile){

    for (int i = 0; i < files.size(); i++)
        if (files[i].countOfChunks > 0)
            files[i].inUse = true;

    int indexMinNumber = 0, tempNumber = 1001;

    vector<int> currentNumbers;
    for (int i = 0; i < files.size(); i++) {
        if (files[i].inUse) {
            ifstreams[i].read((char *)&tempNumber, sizeof(int));
            currentNumbers.push_back(tempNumber);
            if (currentNumbers[indexMinNumber] > tempNumber)
                indexMinNumber = i;
        }else{
            currentNumbers.push_back(1000);
        }
    }

    out.write((char*)&currentNumbers[indexMinNumber], sizeof(int));

    while(!checkMergedCurrentChunk(files)){
        if (!files[indexMinNumber].inUse)
            for (int i = 0; i < files.size(); i++)
                if (files[i].inUse)
                    indexMinNumber = i;

        int pos = ifstreams[indexMinNumber].tellg();
        ifstreams[indexMinNumber].read((char *)&tempNumber, sizeof(int));

        if (ifstreams[indexMinNumber].eof() || tempNumber < currentNumbers[indexMinNumber]) {
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
            out.write((char *) &currentNumbers[indexMinNumber], sizeof(currentNumbers[indexMinNumber]));
        }
    }
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

void outAllFiles(vector<File> &files, startData data) {
    for (int i = 0; i < files.size(); i++) {
        cout << "\n" << i << " file: ";
        ifstream in(files[i].fileName, ios::binary);
        int val;
        in.seekg(0, ios::end);
        int end_file = in.tellg();
        in.seekg(0, ios::beg);
        int j = 1;
        while (in.tellg() != end_file) {
            cout << "\tchunk " << j << ": ";
            for (int i = 0; i < data.sizeOfChunk && in.tellg() != end_file; i++) {
                in.read((char *) &val, sizeof(int));
                cout << val << " ";
            }
            cout << endl;
            j++;
        }
        j = 0;
        in.close();
    }
}

