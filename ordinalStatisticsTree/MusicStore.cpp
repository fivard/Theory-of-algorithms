//
// Created by Acer on 11.02.2021.
//

#include "MusicStore.h"

int Performer::currentFreeId = 0;
int Album::currentFreeId = 0;

string names[] = {"UlysesRivera",
                   "YashReed",
                   "XimenezFlores",
                   "Mike",
                   "Alex",
                   "Dima",
                   "Roma",
                   "AAAAAAA",
                   "Gtgs",
                   "addsasadda"
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

string Performer::getName() {
    return _name;
}
int Performer::getAge() {
    return _age;
}
void Performer::setName(string name){
    _name = name;
}

vector<Performer> Performer::generatingPerformers(int count) {
    int id, age;
    string name;
    vector<Performer> result;
    for (int i = 0; i < count; i++){
        age = rand() % 20 + 20;
        name = names[i];
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

