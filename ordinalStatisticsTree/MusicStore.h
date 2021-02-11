//
// Created by Acer on 11.02.2021.
//

#ifndef ORDINALSTATISTICSTREE_MUSICSTORE_H
#define ORDINALSTATISTICSTREE_MUSICSTORE_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Performer{    int _id;
    string _name;
    int _age;
    vector<int> _albumsId;
    static int currentFreeId;

public:
    Performer();
    Performer(const string& name, int age);
    Performer(const string& name, int age, const vector<int>& albumsId);

    string getName();
    int getAge();
    void setName(string name);
    static vector<Performer> generatingPerformers(int count);

};

class Album{
    int _id;
    string _name;
    int _performersId;
    int _countOfSongs;
    int _cost;
    static int currentFreeId;
public:
    Album();
    Album(const string& name, int performersId, int countOfSongs, int cost);
};


#endif //ORDINALSTATISTICSTREE_MUSICSTORE_H
