#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// тест 4 неправильно проходит

#define alphabet_num 5
#define INFO

class Bohr_Node{
public:
    bool is_end;
    char node_name;
    int node_id;
    int parent;
    int suffix_ref;
    int pattern_num;
    int pattern_length;
    std::vector <int> next_nodes;
public:
    Bohr_Node(): is_end(false), node_name('\0'), node_id(0),
        parent(0), suffix_ref(0), pattern_num(0), pattern_length(0)
    { next_nodes.resize(alphabet_num, 0); }
};

void print(std::vector <Bohr_Node>& bohr, int root_number, unsigned depth){
    for(unsigned i = 0; i < depth; ++i)
        std::cout << "    ";
    if(bohr[root_number].is_end)
        std::cout << "*";
    std::cout << bohr[root_number].node_name
              << bohr[root_number].node_id
              << bohr[root_number].suffix_ref << std::endl;
    for(auto it: bohr[root_number].next_nodes){
        if(it)
            print(bohr, it, depth + 1);
    }
}

void add_str_to_bor(std::vector <Bohr_Node>& bohr, const std::string& str, const int& pattern_num){
    size_t it_bohr = 0;
    for(size_t it_str = 0; it_str < str.size(); ++it_str){
        bool is_sim_contained = false;
        int temp_it_bohr = 0;
        for(size_t it_bohr_next_nodes = 0; it_bohr_next_nodes < bohr[it_bohr].next_nodes.size(); ++it_bohr_next_nodes){
            if(bohr[bohr[it_bohr].next_nodes[it_bohr_next_nodes]].node_name == str[it_str]){
                is_sim_contained = true;
                temp_it_bohr = bohr[bohr[it_bohr].next_nodes[it_bohr_next_nodes]].node_id;
                if(it_str == str.size() - 1){
                    bohr[bohr[it_bohr].next_nodes[it_bohr_next_nodes]].is_end = true;
                    bohr[bohr[it_bohr].next_nodes[it_bohr_next_nodes]].pattern_num = pattern_num;
                    bohr[bohr[it_bohr].next_nodes[it_bohr_next_nodes]].pattern_length = str.size();
                }
            }
        }

        if(!is_sim_contained){
            Bohr_Node new_bohr_node;
            if(it_str != str.size() - 1)
                new_bohr_node.is_end = false;
            else{
                new_bohr_node.is_end = true;
                new_bohr_node.pattern_num = pattern_num;
                new_bohr_node.pattern_length = str.size();
            }
            new_bohr_node.node_name = str[it_str];
            new_bohr_node.node_id = bohr.size();
            new_bohr_node.parent = it_bohr;
            bohr.push_back(new_bohr_node);
            for(size_t i = 0; i < bohr[it_bohr].next_nodes.size(); ++i)
                if(!bohr[it_bohr].next_nodes[i]){
                    bohr[it_bohr].next_nodes[i] = new_bohr_node.node_id;
                    break;
                }
            temp_it_bohr = bohr.size() - 1;
        }
        it_bohr = temp_it_bohr;
    }
}

void set_suffix_reference(std::vector <Bohr_Node>& bohr, int root_number){
    if(!root_number)
        bohr[root_number].suffix_ref = 0;
    else{
        int parent = bohr[root_number].parent;
        if(parent){
            parent = bohr[bohr[root_number].parent].suffix_ref;
            bool is_suff_set = false;
            while(parent && !is_suff_set){
                for(auto it: bohr[parent].next_nodes)
                    if(bohr[it].node_name == bohr[root_number].node_name){
                        bohr[root_number].suffix_ref = bohr[it].node_id;
                        is_suff_set = true;
                    }
                parent = bohr[parent].suffix_ref;
            }

            if(!parent && !is_suff_set)
                for(auto it: bohr[parent].next_nodes)
                    if(bohr[it].node_name == bohr[root_number].node_name)
                        bohr[root_number].suffix_ref = bohr[it].node_id;
        }
    }
    for(auto it: bohr[root_number].next_nodes)
        if(it)
            set_suffix_reference(bohr, it);
}

void find_solution(const std::vector <Bohr_Node>& bohr, const std::string& main_str,
                   std::vector <std::pair <int, int>>& solutions){
    int state = 0;
    for(size_t i = 0; i < main_str.size(); ++i){
        bool is_jump = false;
#ifdef INFO
        std::cout << state << " " << main_str[i] << " -> ";
#endif
        for(auto it: bohr[state].next_nodes)
            if(bohr[it].node_name == main_str[i]){
                state = it;
                is_jump = true;
                break;
            }
        if(!state){
#ifdef INFO
            std::cout << 0 << std::endl;
#endif
            continue;
        }
        // пройти по всем суфф ссылкам до корня
        if(bohr[bohr[state].suffix_ref].is_end && is_jump)
            solutions.push_back(std::make_pair(i - bohr[bohr[state].suffix_ref].pattern_length + 2,
                                                             bohr[bohr[state].suffix_ref].pattern_num + 1));
        int temp_state = state;
        while(temp_state){
            if(bohr[bohr[temp_state].suffix_ref].is_end && is_jump)
                solutions.push_back(std::make_pair(i - bohr[bohr[temp_state].suffix_ref].pattern_length + 2,
                                                                 bohr[bohr[temp_state].suffix_ref].pattern_num + 1));
            temp_state = bohr[bohr[temp_state].suffix_ref].node_id;
        }

        if(!is_jump){
#ifdef INFO
            std::cout << 0 << std::endl;
#endif
            state = bohr[state].suffix_ref;
            --i;
            continue;
        }
        if(!state){
            --i;
#ifdef INFO
            std::cout << 0 << std::endl;
#endif
            continue;
        }
#ifdef INFO
        std::cout << bohr[state].node_id << std::endl;
#endif
        if(bohr[state].is_end)
            solutions.push_back(std::make_pair(i - bohr[state].pattern_length + 2, bohr[state].pattern_num + 1));
    }
}

int main(){
    std::string main_str;
    int num_pattern_str = 0;
    std::cin >> main_str >> num_pattern_str;
    std::vector <std::string> mas_pattern_str(num_pattern_str);
    std::vector <Bohr_Node> bohr;
    bohr.push_back(Bohr_Node());
    for(int i = 0; i < num_pattern_str; ++i){
        std::cin >> mas_pattern_str[i];
        add_str_to_bor(bohr, mas_pattern_str[i], i);
#ifdef INFO
        std::cout << "bor after add: " << mas_pattern_str[i] << std::endl;
        print(bohr, 0, 0);
#endif
    }
    set_suffix_reference(bohr, 0);
#ifdef INFO
    std::cout << "bor after add suffix reference: " << std::endl;
    print(bohr, 0, 0);
#endif
    std::vector <std::pair <int, int>> solutions;
    find_solution(bohr, main_str, solutions);
    solutions.erase(std::unique(solutions.begin(), solutions.end()), solutions.end());
    std::sort(solutions.begin(), solutions.end());
    for(auto it: solutions)
        std::cout << it.first << " " << it.second << std::endl;
    return 0;
}
