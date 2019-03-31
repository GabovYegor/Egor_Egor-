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
    Node* next;
    Node* from;
    bool isVisited;
    int heuristicNumber;
    int priorityNumber;
public:
    Node(): length(0), next(nullptr), isVisited(false), heuristicNumber(0), priorityNumber(0){}
    Node(const char name, const unsigned length, const int heuristicNumber):
        name(name), length(length), next(nullptr), isVisited(false), heuristicNumber(heuristicNumber), priorityNumber(0){}
    void print();
};

void Node::print(){
    Node* currentEl = next;
    std::cout << "\"" << name << "\":   ";
    while (currentEl){
        std::cout << "name: \"" << currentEl->name << "\" length: \"" << currentEl->length
                  << "\" HNum: \"" << currentEl->heuristicNumber << "\", ";
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

int setHeuristicNumber(char finish, char nodeNameTo){
    return abs(int(finish) - int(nodeNameTo));
}

void setNewPriority(Node* head, std::map <char, Node*>& graphList, std::vector <Node*>& queue, const int& priorityBefore){
    for(Node* current = head; current; current = current->next){
        Node* currentInGlobal = graphList.find(current->name)->second;
        if(!currentInGlobal->isVisited){
            if(currentInGlobal->priorityNumber > current->length + current->heuristicNumber + priorityBefore ||
                    currentInGlobal->priorityNumber == 0){
                currentInGlobal->priorityNumber = current->length + current->heuristicNumber + priorityBefore;
                currentInGlobal->from = head;
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

//не так добавляется приоритет
void AStar(const char& nodeNameFrom, const char& nodeNameTo, std::map <char, Node*>& graphList, std::vector <char>& way){
    std::vector <Node*> queue;
    auto searchCurrent = graphList.find(nodeNameFrom);
    Node* current = searchCurrent->second;
    current->isVisited = true;
    current->priorityNumber = 0; // ?
    while(current->name != nodeNameTo){
        setNewPriority(current, graphList, queue, current->priorityNumber); // новый приоритет для соседей current + релоксация элементов очереди
#ifdef INFO
        std::cout << "queue after setNewPriority:  ";
        for(auto it: queue)
            std::cout << "name: \"" << it->name << "\" priopity: \"" << it->priorityNumber << "\",  ";
        std::cout << std::endl;
#endif
        int minPriority = 99999;
        for(auto it: queue){
            if(minPriority > it->priorityNumber){
                minPriority = it->priorityNumber;
                current = it;
            }
        }
#ifdef INFO
        std::cout << "choose best element from queue: " << "name: \"" << current->name
                                                        << "\" priopity: \"" << current->priorityNumber << "\""<< std::endl;
#endif
        current->isVisited = true;
        queue.erase(std::remove(queue.begin(), queue.end(), current), queue.end());
    }
    while(current->name != nodeNameFrom){
        way.push_back(current->name);
        current = current->from;
    }
}

int main(){
    char start, finish, nodeNameFrom, nodeNameTo;
    double currentLength;
    std::cin >> start >> finish;
    std::map <char, Node*> graphList;
    while(std::cin >> nodeNameFrom >> nodeNameTo >> currentLength){
        auto searchFrom = graphList.find(nodeNameFrom);
        auto searchTo = graphList.find(nodeNameTo);
        Node* head;
        if(searchTo == graphList.end()){
            Node* newNode = new Node;
            newNode->name = nodeNameTo;
            graphList.insert(std::pair<char, Node*> (nodeNameTo, newNode));
        }
        if(searchFrom == graphList.end()){
            head = new Node;
            head->name = nodeNameFrom;
            graphList.insert(std::pair<char, Node*> (nodeNameFrom, head));
        }else{
            head = searchFrom->second;
        }
        Node* newElement = new Node(nodeNameTo, currentLength, setHeuristicNumber(finish, nodeNameTo));
        addNode(head, newElement);
    }

#ifdef INFO
    std::cout << "adjacency list: " << std::endl;
    for(auto it: graphList)
        it.second->print();
#endif
    std::vector <char> way;
    AStar(start, finish, graphList, way);
    way.push_back(start);
    for(int i = way.size() - 1; i != -1; --i)
        std::cout << way[i];
    return 0;
}











