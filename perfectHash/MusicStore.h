//
// Created by Acer on 04.02.2021.
//

#ifndef PERFECTHASH_MUSICSTORE_H
#define PERFECTHASH_MUSICSTORE_H

#include <string>
#include <vector>

using namespace std;

class Performer{
    int _id;
    string _name;
    int _age;
    vector<int> _albumsId;
    static int currentFreeId;

public:
    Performer();
    Performer(const string& name, const int age);
    Performer(const string& name, const int age, const vector<int> albumsId);

};


#endif //PERFECTHASH_MUSICSTORE_H
