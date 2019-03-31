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

int algorithmKMP(std::string& main_str, std::string& pattern_str, std::vector <int>& prefixVector){
    size_t itMain = 0, itPattern = 0;
    while(itMain != main_str.size()){
        if(pattern_str[itPattern] == main_str[itMain]){
            if(itMain == main_str.size() - 1 && itPattern != 0){
                return main_str.size() - itPattern - 1;
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
    return -1;
}

int main(){
    std::string main_str;
    std::string pattern_str;
    std::cin >> main_str >> pattern_str;
    if(pattern_str.size() != main_str.size()){
        std::cout << -1 << std::endl;
        return 0;
    }
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
    int itKMP = algorithmKMP(main_str, pattern_str, prefixVector);
    if(itKMP != -1){
        for(int i = 0; i < itKMP; ++i)
            if(main_str[i] != pattern_str[i + pattern_str.size() - itKMP]){
                std::cout << -1;
                return 0;
            }
        std::cout << itKMP;
    }
    else
        std::cout << -1 << std::endl;
    return 0;
}
