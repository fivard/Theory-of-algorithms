//
// Created by Acer on 04.02.2021.
//

#include "MusicStore.h"

int Performer::currentFreeId = 0;

Performer::Performer() {
    _id = currentFreeId++;
    _name = "";
    _age = 0;
    _albumsId.clear();
}

Performer::Performer(const string& name, const int age) {
    _id = currentFreeId++;
    _name = name;
    _age = age;
}

Performer::Performer(const string& name, const int age, const vector<int> albumsId) {
    _id = currentFreeId++;
    _name = name;
    _age = age;
    for (auto i : albumsId)
        _albumsId.push_back(i);
}
