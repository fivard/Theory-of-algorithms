#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int q = 997;
const int size = 100;
int h;

int hash(std::string& word){
    int hash = 0;
    for(char i : word)
        hash = (hash * size + i) % q;
    return hash;
}

bool check(std::vector<std::string>& text, std::vector<std::string>& pattern,
        std::vector<int>& hashed_pattern, std::vector<int>& hashed_text,
           int i_pos, int j_pos){

    for(int i = 0; i < hashed_pattern.size(); i++)
        if(hashed_pattern[i] != hashed_text[i])
            return false;

    for(int i = 0; i < pattern.size(); i++)
        for(int j = 0; j < pattern.size(); j++)
            if(pattern[i][j] != text[i_pos + i][j_pos + j])
                return false;

    return true;
}

std::pair<int, int> rabin_karp(std::vector<std::string>& text, std::vector<std::string>& pattern){
    std::vector<int> hashed_pattern;
    hashed_pattern.reserve(pattern.size());

    for(auto & i : pattern)
        hashed_pattern.push_back(hash(i));


    std::vector<int> hashed_text;
    std::string current_string;

    for(int i = 0; i < text.size() - pattern.size() + 1; i++){

        for(int k = i; k < i +  pattern.size(); k++){
            current_string = text[k].substr(0, pattern.size());
            hashed_text.emplace_back(hash(current_string));
            current_string = "";
        }

        for(int j = 0; j < text.size() - pattern.size() + 1; j++){
            if(check(text, pattern, hashed_pattern, hashed_text, i, j))
                return {i, j};
            else
                for(int k = 0; k < hashed_text.size(); k++)
                    hashed_text[k] = ((hashed_text[k] + text[i + k][j] * (q - h % q)) * size + text[i + k][j + pattern.size()]) % q;
        }
        hashed_text.clear();
    }
    return {-1, -1};
}

int pow(int number, int pow){
    int res = 1;
    for (int i = 0; i < pow; i++)
        res *= number;
    return res;
}

std::vector<std::string> generate_text(int count_of_string){
    std::vector<std::string> text;
    std::string current_string;
    for (int i = 0; i < count_of_string; i++) {
        for (int j = 0; j < count_of_string; j++)
            current_string.push_back(char(rand() % 74) + 48);

        text.push_back(current_string);
        current_string = "";
    }
    return text;
}

int main() {
    std::vector<std::string> text, pattern;
    std::string temp;
    int m, n;

    std::cout << "Enter size of text\n";
    std::cin >> n;
    text = generate_text(n);
    for (int i = 0; i < n; i++)
        std::cout << text[i] << std::endl;

    std::cout << "\nEnter size of pattern\n";
    std::cin >> m;

    std::cout <<"Enter " << m << " strings with length = " << m << " as your pattern\n";
    for(int i = 0; i < m; i++) {
        std::cin >> temp;
        pattern.emplace_back(temp);
    }

    h = pow(size, m - 1);
    std::pair<int, int> shift = rabin_karp(text, pattern);
    if(shift.first == -1){
        std::cout << "No matches were found\n";
    } else {
        std::cout << "A match was found. Shift is " << shift.first << "x" << shift.second << '\n';
    }

    return 0;
}