//
// Created by Acer on 04.02.2021.
//

#include "MusicStore.h"

int Performer::currentFreeId = 0;
int Album::currentFreeId = 0;

string names[3] = {"Ulyses Rivera",
                   "Yash Reed",
                   "Ximenez Flores"
};

Performer::Performer() {
    _id = currentFreeId++;
    _name = "";
    _age = -1;
    _albumsId.clear();
}
Performer::Performer(const string& name, int age) {
    _id = currentFreeId++;
    _name = name;
    _age = age;
}
Performer::Performer(const string& name, int age, const vector<int>& albumsId) {
    _id = currentFreeId++;
    _name = name;
    _age = age;
    for (auto i : albumsId)
        _albumsId.push_back(i);
}

int Performer::getId() {
    return _id;
}
vector<Performer> Performer::generatingPerformers(int count) {
    int id, age;
    string name;
    vector<Performer> result;
    for (int i = 0; i < count; i++){
        age = rand();
        name = names[rand() % 3];
        Performer newPerformer(name, age);
        result.push_back(newPerformer);
    }
    return result;
}

Album::Album() {
    _id = currentFreeId++;
    _name = "";
    _countOfSongs = -1;
    _performersId = -1;
    _cost = -1;
}
Album::Album(const string &name, int performersId, int countOfSongs, int cost) {
    _id = currentFreeId++;
    _name = name;
    _performersId = performersId;
    _countOfSongs = countOfSongs;
    _cost = cost;
}
