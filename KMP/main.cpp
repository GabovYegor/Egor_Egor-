#include <iostream>
#include <string>
#include <vector>

#define INFO

// calculate prefix function
void prefixFunction(const std::string pattern_str, std::vector <int>& prefixVector) {
    size_t i = 1, j = 0;
    prefixVector[0] = 0;
    while (i != pattern_str.size()) {
#ifdef INFO
        std::cout << pattern_str << std::endl;
        for(size_t k = 0; k < i; ++k)
            std::cout << prefixVector[k];
        std::cout << std::endl;
        for(size_t k = 0; k < i; ++k) std::cout << " ";
        std::cout << "|" << std::endl;
        for(size_t k = 0; k < i; ++k) std::cout << " ";
        std::cout << "i" << std::endl;
        for(size_t k = 0; k < j; ++k) std::cout << " ";
        std::cout << "|" << std::endl;
        for(size_t k = 0; k < j; ++k) std::cout << " ";
        std::cout << "j" << std::endl;
#endif
        if (pattern_str[i] == pattern_str[j]) {
            prefixVector[i] = ++j;
#ifdef INFO
            std::cout << "elements of pattern str are equal: ++i; ++j" << std::endl;
            std::cout << "prefix function = " << prefixVector[i] << std::endl;
#endif
            ++i;
        }
        else{
#ifdef INFO
            std::cout << "elements of pattern str are not equal" << std::endl;
#endif
            if (!j){
#ifdef INFO
                std::cout << "j == 0 : prefix function = 0" << std::endl;
#endif
                prefixVector[++i] == 0;
            }
            else{
#ifdef INFO
                std::cout << "j != 0 : j = prefix function(j - 1)" << std::endl;
#endif
                j = prefixVector[j - 1];
            }
        }
    }
}

bool algorithmKMP(std::string& main_str, std::string& pattern_str, std::vector <int>& prefixVector, std::vector <int>& solution) {
    bool hasSolution = false;
    size_t itMain = 0, itPattern = 0; // two iterator for strings
    // while don`t achive end of main string
    while (itMain != main_str.size()) {
#ifdef INFO
        std::cout << main_str << std::endl;
        for(size_t i = 0; i < itMain; ++i) std::cout << " ";
        std::cout << "|" << std::endl;
        for(size_t i = 0; i < itMain - itPattern; ++i) std::cout << " ";
        std::cout << pattern_str << std::endl;
#endif
        if (pattern_str[itPattern] == main_str[itMain]) { // if elements equal
            if (itPattern == pattern_str.size() - 1) { // find solution
#ifdef INFO
                std::cout << "finded solution!!!" << std::endl;
#endif
                solution.push_back(itMain - pattern_str.size() + 1);
                hasSolution = true;
            }
            ++itMain;     // increment
            ++itPattern;  // increment
        }
        else {
            if (!itPattern) { // if iterator pattern string == 0
                ++itMain;
            }
            else {
                itPattern = prefixVector[itPattern - 1]; // set new value for pattern iterator
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
