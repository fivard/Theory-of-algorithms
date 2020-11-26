#include <iostream>

int naive(std::string text, std::string pattern){
    for (int i = 0; i < text.size() - pattern.size(); i++){
        int j = 0;
        while (text[i + j] == pattern[j] && j < pattern.size())
            j++;
        if (j == pattern.size())
            return i;
    }
    return -1;
}

int main() {
    std::string text, pattern;
    int shift;

    std::cout << "Enter a text\n";
    std::cin >> text;
    std::cout << "Enter a pattern\n";
    std::cin >> pattern;

    std::cout << "Naive check: ";
    shift = naive(text, pattern);
    if (shift == -1)
        std::cout << "No matches were found\n";
    else
        std::cout << "A match was found. Shift is " << shift << std::endl;
    
    return 0;
}
