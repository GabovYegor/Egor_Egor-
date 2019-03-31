#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unistd.h>

#define INFO

class Node{
public:
    Node(char name, int length) : next(nullptr), length(length), name(name){}
    Node* next;
    double length;
    char name;
public:

};

class Graph{
public:
    Node* way;
    Graph* from;
    double cost;
    int heuristicNumber;
    double priorityNumber;
    char name;
    bool inComputedSet;
public:
    Graph(char name, int heuristicNumber)
        : way(nullptr), cost(1.79769e+308), heuristicNumber(heuristicNumber), priorityNumber(1.79769e+308), name(name), inComputedSet(false){}
    bool operator ==(const Graph& g){
        return name == g.name;
    }
};

void printAdjacencyList(std::map <char, Graph*>& adjacencyList){
    std::cout << "######## adjacency list #########" << std::endl;
    for(auto iteratorMap: adjacencyList){
        std::cout << " \"" << iteratorMap.first << "\": ";
        for(Node* currentNode = iteratorMap.second->way; currentNode; currentNode = currentNode->next)
            std::cout << "(" << currentNode->name << " " << currentNode->length << "), ";
        std::cout << std::endl;
    }
    std::cout << "#################################" << std::endl;
}

void addNodeToGraph(Graph* graphHead, char nodeTo, int wayLength){
    Node* newNode = new Node(nodeTo, wayLength);
    newNode->next = graphHead->way;
    graphHead->way = newNode;
}

void relaxNeighborhoods(std::map <char, Graph*>& adjacencyList, char newSetElement, int costPrevNode, std::vector <Graph*>& queue){
#ifdef INFO
    std::cout << "recount neighborhoods:" << std::endl;
#endif
    for(Node* currentNeighborhood = adjacencyList.find(newSetElement)->second->way; currentNeighborhood; currentNeighborhood = currentNeighborhood->next){
        Graph* currentNeighborhoodInGlobal = adjacencyList.find(currentNeighborhood->name)->second;
        if(currentNeighborhoodInGlobal->inComputedSet)
            continue;
#ifdef INFO
        std::cout << "\"" << currentNeighborhoodInGlobal->name << "\", old cost: \""
                          << currentNeighborhoodInGlobal->cost << "\", old priority: \""
                          << currentNeighborhoodInGlobal->priorityNumber << "\"" << std::endl;
#endif
        if(currentNeighborhoodInGlobal->cost > costPrevNode + currentNeighborhood->length){
            currentNeighborhoodInGlobal->from = adjacencyList.find(newSetElement)->second;
            currentNeighborhoodInGlobal->cost = costPrevNode + currentNeighborhood->length;
            currentNeighborhoodInGlobal->priorityNumber = currentNeighborhoodInGlobal->heuristicNumber + currentNeighborhoodInGlobal->cost;
#ifdef INFO
            std::cout << "new cost = " << costPrevNode << "(costPrevNode) + "
                      << currentNeighborhood->length << "(length to this node) = " << currentNeighborhoodInGlobal->cost << std::endl;
            std::cout << "new priority = " << currentNeighborhoodInGlobal->cost << "(this cost) + "
                      << currentNeighborhoodInGlobal->heuristicNumber << "(heuristicNumber) = " << currentNeighborhoodInGlobal->priorityNumber << std::endl;
#endif
        }
#ifdef INFO
        else
            std::cout << "old cost is better than " << costPrevNode << "(costPrevNode) + "
                      << currentNeighborhood->length << "(length to this node) = " << currentNeighborhoodInGlobal->cost << std::endl;
#endif
        bool alreadyInQueue = false;
        for(auto it: queue)
            if(it->name == currentNeighborhoodInGlobal->name){
                alreadyInQueue = true;
                break;
            }
        if(!alreadyInQueue){
#ifdef INFO
            std::cout << "push element: \"" << currentNeighborhoodInGlobal->name << "\" to queue" << std::endl << std::endl;
#endif
            queue.push_back(currentNeighborhoodInGlobal);
        }
#ifdef INFO
        else
            std::cout << "element \"" << currentNeighborhoodInGlobal->name << "\" already in queue" << std::endl << std::endl;
#endif
    }
#ifdef INFO
    std::cout << "queue after relax with \"" << newSetElement << "\"" << std::endl;
    for(auto it: queue)
        std::cout << "(\"" << it->name << "\";\"" << it->priorityNumber << "\"), ";
    std::cout << std::endl;
#endif
}

void algorithmAStar(std::map <char, Graph*>& adjacencyList, char start, char finish, std::vector <Graph*>& way){
    Graph* newSetElement = adjacencyList.find(start)->second;
    newSetElement->inComputedSet = true;
    newSetElement->cost = 0;
    std::vector <Graph*> queue;
    while(newSetElement->name != finish){
#ifdef INFO
        std::cout << "#######################################################" << std::endl << std::endl;
        std::cout << "relax with element: name \"" << newSetElement->name << "\" cost \"" << newSetElement->cost << "\"" << std::endl;
#endif
        relaxNeighborhoods(adjacencyList, newSetElement->name, newSetElement->cost, queue);
        int minPriority = 2147483647;
        for(auto it: queue){
            if(minPriority > it->priorityNumber){
                minPriority = it->priorityNumber;
                newSetElement = it;
            }
        }
#ifdef INFO
        std::cout << "best element from queue: " << "name: \"" << newSetElement->name
                                                        << "\" priopity: \"" << newSetElement->priorityNumber << "\"" << std::endl << std::endl;
#endif
        newSetElement->inComputedSet = true;
        queue.erase(std::remove(queue.begin(), queue.end(), newSetElement), queue.end());
    }
    for(Graph* currentWayElement = newSetElement; currentWayElement->name != start; currentWayElement = currentWayElement->from)
        way.push_back(currentWayElement);
}

int main(){
    char start, finish, nodeFrom, nodeTo;
    double wayLength;
    std::map <char, Graph*> adjacencyList;
    std::cin >> start >> finish;
    while (std::cin >> nodeFrom >> nodeTo >> wayLength) {
        auto searchFrom = adjacencyList.find(nodeFrom);
        auto searchTo = adjacencyList.find(nodeTo);
        if(searchTo == adjacencyList.end()){
            Graph* graphHead = new Graph(nodeTo, abs((static_cast<int>(nodeTo) - static_cast<int>(finish))));
            adjacencyList.insert(std::pair<char, Graph*> (nodeTo, graphHead));
        }
        if(searchFrom == adjacencyList.end()){
            Graph* graphHead = new Graph(nodeFrom, abs((static_cast<int>(nodeFrom) - static_cast<int>(finish))));
            addNodeToGraph(graphHead, nodeTo, wayLength);
            adjacencyList.insert(std::pair<char, Graph*> (nodeFrom, graphHead));
        }
        else
            addNodeToGraph(searchFrom->second, nodeTo, wayLength);
    }
#ifdef INFO
    printAdjacencyList(adjacencyList);
#endif
    std::vector <Graph*> way;
    algorithmAStar(adjacencyList, start, finish, way);
    std::cout << start;
    for(int i = way.size() - 1; i != -1; --i)
        std::cout << way[i]->name;
    return 0;
}
