#include <iostream>
#include <vector>

std::vector<int> KMP(std::string s){
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
    return prefix;
}

int main() {
    std::string mainText, _template;
    std::cout << "Enter two examples\n";
    std::cin >> mainText >> _template;

    mainText += mainText;
    std::vector<int> answer = KMP(_template + mainText);

    int id = -1;
    for (int i = 0; i < answer.size(); i++){
        std::cout << answer[i] << " ";
        if (answer[i] == _template.size()) {
            id = i;
        }
    }


    if (id == -1)
        std::cout << "\nIsn't cyclic shifted string\n";
    else
        std::cout << "\nIs cyclic shifted string. Shift equal to " << id - _template.size() - answer[id] + 1;

    return 0;
}
