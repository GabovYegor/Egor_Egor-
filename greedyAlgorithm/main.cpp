#include <iostream>
#include <map>

class Node{
public:
    double length;
    std::string name;
    class Node* next;
public:
    Node(){}
    Node(const std::string name, const unsigned length): name(name), length(length), next(nullptr){}
    void print(){
        Node* currentEl = next;
        while (currentEl){
            std::cout << currentEl->name << currentEl->length << "--->";
            currentEl = currentEl->next;
        }
        std::cout << std::endl;
    }
};

void addNode(Node*& head, Node* newElement){
    Node* current = head;
    while(current->next)
       current = current->next;
    current->next = newElement;
}

void greedyAlgorithm(std::map <std::string, Node*>& graphList, std::string nodeNameFrom, std::string nodeNameTo){
    if(nodeNameFrom == nodeNameTo)
        return;
    auto searchHead = graphList.find(nodeNameFrom);
    Node* current = searchHead->second->next;
    unsigned minLength = 99999;
    std::string minKey;
    while(current){
        if(current->length < minLength){
            minKey = current->name;
            minLength = current->length;
        }
        current = current->next;
    }
    std::cout << minKey;
    greedyAlgorithm(graphList, minKey, nodeNameTo);
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
    for(auto it = graphList.begin(); it != graphList.end(); ++it){
        std::cout << it->first << "--->";
        it->second->print();
    }
    std::cout << start;
    greedyAlgorithm(graphList, start, finish);
    return 0;
}
