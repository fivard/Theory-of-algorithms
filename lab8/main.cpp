#include <iostream>
#include <vector>

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
int size = 100;

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

    for (int i = 0; i < pattern.size(); i++)
        if (text[shift + i] != pattern[i])
            return false;

    return true;
}

int rabin_carp(const std::string& text, const std::string& pattern){

}

int main() {
    std::string text, pattern;
    int shift;

    std::cout << "Enter a text\n";
    std::cin >> text;
    std::cout << "Enter a pattern\n";
    std::cin >> pattern;

    std::cout << "\nNaive check: ";
    shift = naive(text, pattern);
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift << std::endl;

    std::cout << "\nKMP: ";
    shift = KMP(text, pattern);
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift << std::endl;
    
    return 0;
}
