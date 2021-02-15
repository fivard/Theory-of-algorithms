#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <ctime>

///---------------------------------------------Naive------------------------------------------------///

int naive(const std::string& text, const std::string& pattern){
    for (int i = 0; i <= text.size() - pattern.size(); i++){
        int j = 0;
        while (text[i + j] == pattern[j] && j < pattern.size())
            j++;
        if (j == pattern.size())
            return i;
    }
    return -1;
}

///--------------------------------------------KMP----------------------------------------------------///

int KMP(const std::string& text, const std::string& pattern){
    std::string s = pattern+text;
    int n = s.length();
    std::vector<int> prefix(n);
    for (int i = 1; i < n; i++){
        int countMatched = prefix[i-1];
        while (countMatched > 0 && s[i] != s[countMatched])
            countMatched = prefix[countMatched - 1];
        if (s[i] == s[countMatched])
            countMatched++;
        prefix[i] = countMatched;
    }
    for (int i = 0; i < prefix.size(); i++)
        if (prefix[i] == pattern.size())
            return i - pattern.size() - prefix[i]+1;

    return -1;
}

///----------------------------------------------Rabin-Carp---------------------------------------------///

int q = 997;
int size = 200;

int hash(const std::string& word){
    int hash = 0;

    for (int i = 0; i < word.size(); i++)
        hash = (hash*size + word[i]) % q;

    return hash;
}

bool check(const std::string& text, const std::string& pattern,
           const int& hashed_text, const int& hashed_pattern,
           const int& shift){

    if (hashed_pattern != hashed_text)
        return false;

    for (int i = 0; i < pattern.size(); i++) {
        if (text[shift + i] != pattern[i])
            return false;
    }

    return true;
}

int pow(int number, int pow){
    int res = 1;
    for (int i = 0; i < pow; i++)
        res *= number;
    return res;
}

int rabin_carp(const std::string& text, const std::string& pattern){
    std::string current_text;
    int hashed_text, hashed_pattern;
    int h = pow(size, pattern.size() - 1);

    current_text = text.substr(0, pattern.size());
    hashed_pattern = hash(pattern);
    hashed_text = hash(current_text);
    if (check(text, pattern, hashed_text, hashed_pattern, 0))
        return 0;

    for (int i = 0; i < text.size() - pattern.size(); i++){
        hashed_text = ((hashed_text + text[i] * (q - h % q)) * size + text[i + pattern.size()]) % q;

        if (check(text, pattern, hashed_text, hashed_pattern, i+1))
            return i+1;
    }

    return -1;
}

///--------------------------------------------Horspul-------------------------------------------///

int horspul(const std::string& text, const std::string& pattern){

    std::map<char, int> shifts;

    for(int i = 0; i < text.size(); i++)
        shifts[text[i]] = pattern.size();

    for(int i = 0; i < pattern.size() - 1; i++)
        shifts[pattern[i]] = pattern.size() - i - 1;

    int i = pattern.size() - 1, k;

    while (i < text.size()){
        k = 0;
        while (k < pattern.size() && pattern[pattern.size() - k - 1] == text[i - k])
            k++;

        if(k == pattern.size())
            return i - pattern.size() + 1;
        else
            i += shifts[text[i]];
    }

    return -1;
}

///--------------------------------------------Boyer-Moor-----------------------------------------------------///

int boyer_moor(const std::string& text, const std::string& pattern){

    std::map<char, int> shifts;

    for(int i = 0; i < text.size(); i++)
        shifts[text[i]] = pattern.size();

    for(int i = 0; i < pattern.size() - 1; i++)
        shifts[pattern[i]] = pattern.size() - i - 1;

    std::vector<int> suffix (pattern.size() - 1, 0);
    for (int j = 1, maxZidx = 0, maxZ = 0; j < pattern.size(); ++j) {
        if (j <= maxZ) suffix[j] = std::min(maxZ - j + 1, suffix[j - maxZidx]);
        while (j + suffix[j] < pattern.size() && text[pattern.size() - 1 - suffix[j]] == text[pattern.size() - 1 - (j + suffix[j])])
            suffix[j]++;
        if (j + suffix[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + suffix[j] - 1;
        }
    }

    int i = 0;
    while (i <= pattern.size() - text.size()) {
        int j = 0;
        for (j = pattern.size() - 1; j >= 0 && pattern[j] == text[i + j]; --j);
        if (j < 0) {
            return i;
        }
        else i += std::max((suffix[j + 1]), (int)(shifts[text[i + j]] - pattern.size() + j + 1));
    }
    return -1;
}

int main() {
    std::string text, pattern;
    int shift;
    clock_t start, end;

    std::cout << "Enter a text\n";
    std::cin >> text;
    std::cout << "Enter a pattern\n";
    std::cin >> pattern;

    std::cout << "\nNaive check: ";
    start = clock();
    shift = naive(text, pattern);
    end = clock();
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift;
    std::cout << ". Time is " << end - start << std::endl;

    std::cout << "\nKMP: ";
    start = clock();
    shift = KMP(text, pattern);
    end= clock();
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift;
    std::cout << ". Time is " << end - start << std::endl;

    std::cout << "\nRabin-Carp: ";
    start = clock();
    shift = rabin_carp(text, pattern);
    end = clock();
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift;
    std::cout << ". Time is " << end - start << std::endl;

    std::cout << "\nHorspul: ";
    start = clock();
    shift = horspul(text, pattern);
    end = clock();
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift;
    std::cout << ". Time is " << end - start << std::endl;

    std::cout << "\nBoyer moor: ";
    start = clock();
    shift = boyer_moor(text, pattern);
    end = clock();
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift;
    std::cout << ". Time is " << end - start << std::endl;

    return 0;
}
