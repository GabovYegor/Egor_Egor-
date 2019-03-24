#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#define INFO

class Node{
public:
    char name;
    double length;
    class Node* next;
    bool isVisited;
    int heuristicNumber;
    int priorityNumber;
public:
    Node(): length(0), next(nullptr), isVisited(false), heuristicNumber(0), priorityNumber(0){}
    Node(const char name, const unsigned length, const int heuristicNumber):
        name(name), length(length), next(nullptr), isVisited(false), heuristicNumber(heuristicNumber), priorityNumber(0){}
    void print() const;
};

void Node::print() const{
    Node* currentEl = next;
    while (currentEl){
        std::cout << currentEl->name << currentEl->length << currentEl->heuristicNumber << ", ";
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

void setNewPriorite(Node* head, std::map <char, Node*>& graphList, std::vector <Node*>& queue, const int& priorityBefore){
    for(Node* current = head; current; current = current->next){
        Node* currentInGlobal = graphList.find(current->name)->second; // когда w приходит все плохо
        if(!currentInGlobal->isVisited){
            if(currentInGlobal->priorityNumber > current->length + current->heuristicNumber + priorityBefore ||
                    currentInGlobal->priorityNumber == 0){
                currentInGlobal->priorityNumber = current->length + current->heuristicNumber + priorityBefore;
                bool alreadyInQueue = false;
                for(auto it: queue)
                    if(it->name == currentInGlobal->name){
                        alreadyInQueue = true;
                        break;
                    }
                if(!alreadyInQueue){
                    queue.push_back(currentInGlobal);
                }
            }
        }
    }
}

void AStar(const char& nodeNameFrom, const char& nodeNameTo, std::map <char, Node*>& graphList){
    std::vector <Node*> queue; // char
    auto searchCurrent = graphList.find(nodeNameFrom);
    Node* current = searchCurrent->second;
    current->isVisited = true;
    current->priorityNumber = 0;
    while(1){
        if(current->name == nodeNameTo)
            break;
        setNewPriorite(current, graphList, queue, current->priorityNumber);
        for(auto it: queue)
            std::cout << it->name << it->priorityNumber << it->length << " ";
        int minPriority = 99999;
        for(auto it: queue){
            if(minPriority > it->priorityNumber){
                minPriority = it->priorityNumber;
                current = it;
            }
        }
        std::cout << "current " << current->name << current->priorityNumber << current->length << " ";
        current->isVisited = true;
        queue.erase(std::remove(queue.begin(), queue.end(), current), queue.end());
        for(auto it: queue)
            std::cout << it->name << it->priorityNumber << it->length << " ";
    }
}

int setHeuristicNumber(char finish, char nodeNameTo){
    return abs(int(finish) - int(nodeNameTo));
}

int main(){
    char start, finish, nodeNameFrom, nodeNameTo;
    double currentLength;
    std::cin >> start >> finish;
    std::map <char, Node*> graphList;
    while(std::cin >> nodeNameFrom >> nodeNameTo >> currentLength){
        auto search = graphList.find(nodeNameFrom);
        Node* head;
        if(search == graphList.end()){
            head = new Node;
            head->name = nodeNameFrom;
            graphList.insert(std::pair<char, Node*> (nodeNameFrom, head));
        }else{
            head = search->second;
        }
        Node* newElement = new Node(nodeNameTo, currentLength, setHeuristicNumber(finish, nodeNameTo));
        addNode(head, newElement);
    }

#ifdef INFO
    for(auto it: graphList){
        std::cout << it.first << ":  ";
        it.second->print();
    }
#endif
    AStar(start, finish, graphList);
    return 0;
}











