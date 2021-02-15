#include "MusicStore.h"

int p = 101;

class HashRow{
public:
    unsigned int a;
    unsigned int b;
    unsigned int size;

    Performer* performers;
};

int mod = 137;

int hashString(const string& str){
    int result = 0;
    int m = 1, k = 31;
    for (int i = 0; i < str.size(); i++) {
        result += ((int) str[i] * m) % mod;
        m = (m * k) % mod;
    }
    return result;
}

int universalHash(const string& key, int a, int b, int m){
    int stringHash = hashString(key);
    cout << stringHash << '\n';
    return ((a*stringHash + b) % p) % m;
}

void perfectHashing(HashRow* perfectHashTable, vector<Performer>& performers){
    vector<vector<Performer>> countHashes;
    countHashes.resize(performers.size());
    cout << performers.size() << '\n';
    for (int i = 0; i < performers.size(); i++){
        int hash = universalHash(performers[i].getName(), 3, 88, performers.size());
        countHashes[hash].push_back(performers[i]);
    }
    for (int i = 0; i < performers.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < countHashes[i].size(); j++)
            cout << countHashes[i][j].getName() << " ";
        cout << '\n';
    }

    for (int i = 0; i < performers.size(); i++){
        if (!countHashes[i].empty()){
            /// if hash cell contains only one hash
            perfectHashTable[i].performers = new Performer[countHashes[i].size() * countHashes[i].size()];
            perfectHashTable[i].size = countHashes[i].size() * countHashes[i].size();

            if (countHashes[i].size() == 1){
                perfectHashTable[i].performers[0] = countHashes[i][0];
                perfectHashTable[i].a = perfectHashTable[i].b = 0;
                continue;
            }
            /// if hash cell contains more than one hash
            bool perfectHashed = false, sameHash = false;
            int* usedHash = new int[countHashes[i].size() * countHashes[i].size()];
            for (int j = 0; j < countHashes[i].size() * countHashes[i].size(); j++)
                usedHash[i] = 0;
            perfectHashTable[i].b = perfectHashTable[i].a = 1;

            // perfect hashing one cell
            while (!perfectHashed){
                // trying to geuss the a and b for perfect hashing
                for (int j = 0; j < countHashes[i].size(); j++) {
                    int hash = universalHash(countHashes[i][j].getName(),
                                             perfectHashTable[i].a,
                                             perfectHashTable[i].b,
                                             perfectHashTable[i].size);
                    if (usedHash[hash] != 0)
                        sameHash = true;
                }
                if (sameHash) {
                    sameHash = false;
                    if (perfectHashTable[i].a == p - 1) {
                        perfectHashTable[i].a = 1;
                        perfectHashTable[i].b++;
                    } else {
                        perfectHashTable[i].a++;
                    }
                    continue;
                //  we geussed right parameters, add to hash table
                } else {
                    perfectHashed = true;
                    for (int j = 0; j < perfectHashTable[i].size; j++)
                        perfectHashTable[i].performers[j].setName("empty");
                    for (int j = 0; j < countHashes[i].size(); j++) {
                        int hash = universalHash(countHashes[i][j].getName(),
                                                 perfectHashTable[i].a,
                                                 perfectHashTable[i].b,
                                                 perfectHashTable[i].size);
                        perfectHashTable[i].performers[hash] = countHashes[i][j];
                    }
                }
            }
        }
    }

}

int main() {
    int m;
    cout << "Enter count of keys:";
    cin >> m;
    cout << "\n...Generating " << m << " performers\n";
    vector<Performer> performers;
    performers = Performer::generatingPerformers(m);
    HashRow* perfectHashTable = new HashRow[m];
    for (int i = 0; i < m; i++) {
        perfectHashTable[i].a = perfectHashTable[i].b = perfectHashTable[i].size = 0;
        perfectHashTable[i].performers = nullptr;
    }
    cout << "...Hashing\n";
    perfectHashing(perfectHashTable, performers);
    cout << "Perfect\n";
    cout << "HashTable:\n";
    for (int i = 0; i < performers.size(); i++){
        cout << i << ": ";
        if (perfectHashTable[i].performers == nullptr)
            cout << "Empty hash cell\n";
        else{
            for (int j = 0; j < perfectHashTable[i].size; j++)
                cout << " { " << perfectHashTable[i].performers[j].getName() << ", "
                                << perfectHashTable[i].performers[j].getAge() << "} ";
            cout << '\n';
        }
    }

    delete [] perfectHashTable;

    return 0;
}
