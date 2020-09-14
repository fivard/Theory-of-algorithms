//
// Created by Admin on 10.09.2020.
//

#ifndef MULTIPHASE_SORTING_FILES_H
#define MULTIPHASE_SORTING_FILES_H

#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

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
    int countOfChunks;
    vector<int> currentChunk;
    bool inUse;
};

using namespace std;

void fillFileWithNumbers(const startData data);
void countSizeOfFiles(vector<int> &countsOfChunkInEachFiles, const startData data);
void setFilesNameAndCountsOfChunks(vector<File> &files, const startData data, vector<int> countsOfChunksInEachFiles);
string mergeSort(vector<File> &files);
void mergeCurrentChunk(vector<File> &files,vector<ifstream> &ifstreams, const int indexOutputFile);
void mergeCurrentChunkAppend(vector<File> &files,vector<ifstream> &ifstreams, const int indexOutputFile);
int getIndexMinFile(vector<File> &files);
int getIndexOutputFile(vector<File> &files);
bool checkMergedCurrentChunk(vector<File> &files);
bool checkMergedAllFiles(vector<File> &files);
#endif //MULTIPHASE_SORTING_FILES_H
