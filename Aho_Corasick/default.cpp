//void add_pattern_to_bor(std::vector <Bohr_Node>& bohr, const std::string& pattern){
//    for(auto it_pattern: pattern){
//        int it_bohr = 0;
//        bool flag = false;
//        for(auto it_bohr_next_nodes : bohr[it_bohr].next_nodes){
//            if(it_bohr_next_nodes.node_name == it_pattern)
//                flag = true;
//        }
//        if(!flag){
//            Bohr_Node new_bohr_node;
//            // добавить is_end
//            new_bohr_node.node_id = bohr.size();
//            new_bohr_node.node_name = it_pattern;
//            new_bohr_node.suffix_link = 0;
//            bohr.push_back(new_bohr_node);
//            // добавить проверку
//            bohr[it_bohr].next_nodes[0] = new_bohr_node;
//        }
//        it_bohr = bohr.size() - 1;
//    }
//}

//aerthj
//6
//abb
//bab
//ba
//cb
//cac
//c
