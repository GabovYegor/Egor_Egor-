#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#define INFO

class Node{
public:
    std::string name;
    double length;
    class Node* next;
    bool isVisited;
public:
    Node(): name(""), length(0), next(nullptr), isVisited(false){}
    Node(const std::string name, const unsigned length): name(name), length(length), next(nullptr), isVisited(false){}
    void print();
};

void Node::print(){
    Node* currentEl = next;
    while (currentEl){
        std::cout << currentEl->name << currentEl->length << ", ";
        currentEl = currentEl->next;
    }
    std::cout << std::endl;
}

void addNode(Node*& head, Node* newElement){
    Node* current = head;
    while(current->next)
       current = current->next;
    current->next = newElement;
}

bool greedySort(const Node* a, const Node* b){
    return a->length < b->length;
}

bool greedyAlgorithm(const std::map <std::string, Node*>& graphList, const std::string& nodeNameFrom,
                     const std::string& nodeNameTo, std::vector <std::string>& solution){
    if(nodeNameFrom == nodeNameTo)
        return true;
    auto searchHead = graphList.find(nodeNameFrom);
    if(searchHead->second->isVisited)
        return false;
    searchHead->second->isVisited = true;
    std::vector <Node*> sortKeys;
    Node* current = searchHead->second->next;  // sort by length
    while(current){
        sortKeys.push_back(current);
        current = current->next;
    }
    if(sortKeys.empty())
        return false;

#ifdef INFO
    std::cout << "sort ways in node: " << searchHead->first << std::endl;
    if(sortKeys.size())
        for(auto it: sortKeys)
            std::cout << it->name << it->length << " ";
    std::cout << std::endl;
#endif

    std::sort(sortKeys.begin(), sortKeys.end(), greedySort);

    for(auto it: sortKeys){
        if(greedyAlgorithm(graphList, it->name, nodeNameTo, solution)){
            solution.push_back(it->name);
            return true;
        }
    }

    return false;
}

int main(){
    std::string start, finish, nodeNameFrom, nodeNameTo;
    double currentLength;
    std::cin >> start >> finish;
    std::map <std::string, Node*> graphList;
    while(std::cin >> nodeNameFrom >> nodeNameTo >> currentLength){
        auto search = graphList.find(nodeNameFrom);
        Node* head;
        if(search == graphList.end()){
            head = new Node;
            graphList.insert(std::pair<std::string, Node*> (nodeNameFrom, head));
        }else{
            head = search->second;
        }
        Node* newElement = new Node(nodeNameTo, currentLength);
        addNode(head, newElement);
    }

#ifdef INFO
    for(auto it: graphList){
        std::cout << it.first << ":  ";
        it.second->print();
    }
#endif
    std::vector <std::string> solution;
    solution.push_back(finish);
    greedyAlgorithm(graphList, start, finish, solution);
    solution.push_back(start);
    for(int i = solution.size() - 1; i != 0; --i)
        std::cout << solution[i];
    return 0;
}
