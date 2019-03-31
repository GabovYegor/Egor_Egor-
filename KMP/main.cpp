#include <iostream>
#include <string>
#include <vector>

//#define INFO

void prefixFunction(const std::string pattern_str, std::vector <int>& prefixVector){
    size_t i = 1, j = 0;
    prefixVector[0] = 0;
    while (i != pattern_str.size()) {
        if(pattern_str[i] == pattern_str[j]){
            prefixVector[i] = ++j;
            ++i;
        }
        else
            if(!j)
                prefixVector[i++] == 0;
            else
                j = prefixVector[j - 1];
    }
}

bool algorithmKMP(std::string& main_str, std::string& pattern_str, std::vector <int>& prefixVector, std::vector <int>& solution){
    bool hasSolution = false;
    size_t itMain = 0, itPattern = 0;
    while(itMain != main_str.size()){
        if(pattern_str[itPattern] == main_str[itMain]){
            if(itPattern == pattern_str.size() - 1){
                solution.push_back(itMain - pattern_str.size() + 1);
                hasSolution = true;
            }
            ++itMain;
            ++itPattern;
        }
        else{
            if(!itPattern)
                ++itMain;
            else
                itPattern = prefixVector[itPattern - 1];
        }
    }
    return hasSolution;
}

int main(){
    std::string main_str;
    std::string pattern_str;
    std::cin >> pattern_str >> main_str;
    std::vector <int> prefixVector(pattern_str.size());
    prefixFunction(pattern_str, prefixVector);
#ifdef INFO
    std::cout << "source string: " << main_str << std::endl
              << "pattern string: " << pattern_str << std::endl;
    std::cout << "prefix vector: ";
    for(auto it: prefixVector)
        std::cout << it << " ";
    std::cout << std::endl;
#endif
    std::vector <int> solution;
    if(algorithmKMP(main_str, pattern_str, prefixVector, solution)){
        for(size_t i = 0; i < solution.size() - 1; ++i)
            std::cout << solution[i] << ",";
        std::cout << solution[solution.size() - 1] << std::endl;
    }
    else
        std::cout << -1 << std::endl;
    return 0;
}
