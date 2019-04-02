#include <iostream>
#include <string>
#include <vector>

//#define INFO

// calculate prefix function
void prefixFunction(const std::string pattern_str, std::vector <int>& prefixVector) {
    size_t i = 1, j = 0;
    prefixVector[0] = 0;
    while (i != pattern_str.size()) {
        if (pattern_str[i] == pattern_str[j]) {
            prefixVector[i] = ++j;
            ++i;
        }
        else
            if (!j)
                prefixVector[i++] == 0;
            else
                j = prefixVector[j - 1];
    }
}

bool algorithmKMP(std::string& main_str, std::string& pattern_str, std::vector <int>& prefixVector, std::vector <int>& solution) {
    bool hasSolution = false;
    size_t itMain = 0, itPattern = 0; // two iterator for strings
    // while don`t achive end of main string
    while (itMain != main_str.size()) {
        if (pattern_str[itPattern] == main_str[itMain]) { // if elements equal
#ifdef INFO
            std::cout << "Pattent element: " << itPattern << "(" << pattern_str[itPattern] << ")" << "=="
                << "String element: " << itMain << "(" << main_str[itMain] << ")" << std::endl;
#endif
            if (itPattern == pattern_str.size() - 1) { // find solution
                solution.push_back(itMain - pattern_str.size() + 1);
                hasSolution = true;
#ifdef INFO
                std::cout << "finded pattern in string!!!" << std::endl;
#endif
            }
            ++itMain;     // increment
            ++itPattern;  // increment
        }
        else {
#ifdef INFO
            std::cout << "Pattern element: " << itPattern << "(" << pattern_str[itPattern] << ")" << "!="
                << "String element: " << itMain << "(" << main_str[itMain] << ")" << std::endl;
#endif
            if (!itPattern) { // if iterator pattern string == 0
                ++itMain;
#ifdef INFO
                std::cout << "itPattern == 0 => ++itMain" << std::endl;
                std::cout << "new value of itMain: " << itMain << std::endl;
#endif
            }
            else {
                itPattern = prefixVector[itPattern - 1]; // set new value for pattern iterator
#ifdef  INFO
                std::cout << "new value of itPattern: " << itPattern << std::endl;
#endif
            }
        }
    }
    return hasSolution;
}

int main() {
    std::string main_str;
    std::string pattern_str;
    std::cin >> pattern_str >> main_str;
    std::vector <int> prefixVector(pattern_str.size()); // vector with prefix function
    prefixFunction(pattern_str, prefixVector); // calculate prefix function
#ifdef INFO
    std::cout << "source string: " << main_str << std::endl
        << "pattern string: " << pattern_str << std::endl;
    std::cout << "prefix vector: ";
    for (auto it : prefixVector)
        std::cout << it << " ";
    std::cout << std::endl;
#endif
    std::vector <int> solution;
    if (algorithmKMP(main_str, pattern_str, prefixVector, solution)) { // have solution???
        for (size_t i = 0; i < solution.size() - 1; ++i)
            std::cout << solution[i] << ",";
        std::cout << solution[solution.size() - 1] << std::endl;
    }
    else
        std::cout << -1 << std::endl; // if main string don`t constain pattern string
    return 0;
}
