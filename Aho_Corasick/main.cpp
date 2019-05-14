#include <iostream>
#include <vector>
#include <string>

#define alphabet_num 5

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
        std::cout << "E";
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
        if(!parent)
            bohr[root_number].suffix_ref = 0;
        else{
            parent = bohr[parent].suffix_ref;
            for(auto it: bohr[parent].next_nodes)
                if(bohr[it].node_name == bohr[root_number].node_name)
                    bohr[root_number].suffix_ref = bohr[it].node_id;
            if(!bohr[root_number].suffix_ref)
                parent = bohr[parent].suffix_ref;
        }
    }
    for(auto it: bohr[root_number].next_nodes)
        if(it)
            set_suffix_reference(bohr, it);
}

void find_solution(const std::vector <Bohr_Node>& bohr, const std::string& main_str){
    int state = 0;
    for(size_t i = 0; i < main_str.size(); ++i){
        bool is_jump = false;
        std::cout << state << " " << main_str[i] << " -> ";
        for(auto it: bohr[state].next_nodes)
            if(bohr[it].node_name == main_str[i]){
                state = it;
                is_jump = true;
            }
        if(!is_jump)
            state = bohr[state].suffix_ref;
        if(!state){
            --i;
            std::cout << 0 << std::endl;
            continue;
        }
        std::cout << bohr[state].node_id << std::endl;
        if(bohr[state].is_end)
            std::cout << i - bohr[state].pattern_length + 2 << " " << bohr[state].pattern_num + 1 << std::endl;
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
    }
    set_suffix_reference(bohr, 0);
    print(bohr, 0, 0);
    find_solution(bohr, main_str);
    return 0;
}
