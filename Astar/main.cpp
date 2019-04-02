#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

//#define INFO
#define LABA

// node of graph
class Node {
public:
    Node(char name, int length) : next(nullptr), length(length), name(name) {}
    Node* next;
    double length;
    char name;
public:
    ~Node() {
        if (next)
            delete next;
    }
};

// graph
class Graph {
public:
    Node* way; // where we can go
    Graph* from; // from here went
    double cost;
    int heuristicNumber;
    double priorityNumber;
    char name;
    bool inComputedSet;
public:
    Graph(char name, int heuristicNumber)
        : way(nullptr), cost(1.79769e+308), heuristicNumber(heuristicNumber), priorityNumber(1.79769e+308), name(name), inComputedSet(false) {}
    ~Graph() {
        delete way;
    }
    bool operator ==(const Graph& g) {
        return name == g.name;
    }

};

 // print adjacency list
void printAdjacencyList(std::map <char, std::shared_ptr <Graph>>& adjacencyList) {
    std::cout << "######## adjacency list #########" << std::endl;
    for (auto iteratorMap : adjacencyList) {
        std::cout << " \"" << iteratorMap.first << "\": ";
        for (Node* currentNode = iteratorMap.second->way; currentNode; currentNode = currentNode->next)
            std::cout << "(" << currentNode->name << " " << currentNode->length << "), ";
        std::cout << std::endl;
    }
    std::cout << "#################################" << std::endl;
}

// add node to the adjacency list
void addNodeToGraph(Graph* graphHead, char nodeTo, int wayLength) {
    Node* newNode = new Node(nodeTo, wayLength);
    newNode->next = graphHead->way;
    graphHead->way = newNode;
}

// relax neighborhoods
void relaxNeighborhoods(std::map <char, std::shared_ptr <Graph>>& adjacencyList, char newSetElement, int costPrevNode, std::vector <Graph*>& queue) {
#ifdef INFO
    std::cout << "recount neighborhoods:" << std::endl;
#endif
    for (Node* currentNeighborhood = adjacencyList.find(newSetElement)->second->way; currentNeighborhood; currentNeighborhood = currentNeighborhood->next) {
        Graph* currentNeighborhoodInGlobal = adjacencyList.find(currentNeighborhood->name)->second.get(); // find info about node in graph
        if (currentNeighborhoodInGlobal->inComputedSet) // if already if computed set
            continue;
#ifdef INFO
        std::cout << "\"" << currentNeighborhoodInGlobal->name << "\", old cost: \""
            << currentNeighborhoodInGlobal->cost << "\", old priority: \""
            << currentNeighborhoodInGlobal->priorityNumber << "\"" << std::endl;
#endif
        if (currentNeighborhoodInGlobal->cost > costPrevNode + currentNeighborhood->length) { // if cost better than before
            currentNeighborhoodInGlobal->from = adjacencyList.find(newSetElement)->second.get();
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
        // check is node alredy in priopity queue
        bool alreadyInQueue = false;
        for (auto it : queue)
            if (it->name == currentNeighborhoodInGlobal->name) {
                alreadyInQueue = true;
                break;
            }
        if (!alreadyInQueue) { // add element ro priority queue
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
    for (auto it : queue)
        std::cout << "(\"" << it->name << "\";\"" << it->priorityNumber << "\"), ";
    std::cout << std::endl;
#endif
}

// Astar algorithm
void algorithmAStar(std::map <char, std::shared_ptr<Graph>>& adjacencyList, char start, char finish, std::vector <Graph*>& way) {
    Graph* newSetElement = adjacencyList.find(start)->second.get(); //
    newSetElement->inComputedSet = true;							// first init
    newSetElement->cost = 0;										//
    std::vector <Graph*> queue; // priority queue
    while (newSetElement->name != finish) {
#ifdef INFO
        std::cout << "#######################################################" << std::endl << std::endl;
        std::cout << "relax with element: name \"" << newSetElement->name << "\" cost \"" << newSetElement->cost << "\"" << std::endl;
#endif
        relaxNeighborhoods(adjacencyList, newSetElement->name, newSetElement->cost, queue); // relaxtion heiborhoods current node
        int minPriority = 2147483647;
        for (auto it : queue) { // select minimul queue element
            if (minPriority > it->priorityNumber) {
                minPriority = it->priorityNumber;
                newSetElement = it;
            }
        }
#ifdef INFO
        std::cout << "best element from queue: " << "name: \"" << newSetElement->name
            << "\" priopity: \"" << newSetElement->priorityNumber << "\"" << std::endl << std::endl;
#endif
        newSetElement->inComputedSet = true; // set flag that we was in this node and node already has best cost and priority
        queue.erase(std::remove(queue.begin(), queue.end(), newSetElement), queue.end()); // delete node from priority queue
    }
#ifdef INFO
    std::cout << "#######################################################" << std::endl << std::endl;
#endif
    for (Graph* currentWayElement = newSetElement; currentWayElement->name != start; currentWayElement = currentWayElement->from) // memery way
        way.push_back(currentWayElement);
}

int main() {
    char start, finish, nodeFrom, nodeTo;
    double wayLength;
    std::map <char, std::shared_ptr <Graph>> adjacencyList; // declaration start and finish
#ifdef INFO
    std::cout << "set start node: ";
    std::cin >> start;
    std::cout << "set finish node: ";
    std::cin >> finish;
#else
    std::cin >> start >> finish; // set start and finish nodes
#endif

#ifndef INFO
    while(std::cin >> nodeFrom >> nodeTo >> wayLength){
#else
    std::cout << "set edge: ";
    for(; std::cin >> nodeFrom >> nodeTo >> wayLength; std::cout << "set next edge :"){
#endif
        auto searchFrom = adjacencyList.find(nodeFrom);
        auto searchTo = adjacencyList.find(nodeTo);
        if (searchFrom == adjacencyList.end()) { // if adjacency list isn`t contain node from
#ifdef LABA
            int heuristicNumber = 0;
            std::cout << "set heuristic number for node \"" << nodeFrom << "\": ";
            std::cin >> heuristicNumber;
            Graph* graphHead = new Graph(nodeFrom, 0);
#else
            Graph* graphHead = new Graph(nodeFrom, abs((static_cast<int>(nodeFrom) - static_cast<int>(finish))));
#endif
            addNodeToGraph(graphHead, nodeTo, wayLength);
            adjacencyList.insert(std::pair<char, Graph*>(nodeFrom, graphHead)); // add to adjacency list node from
        }
        else
            addNodeToGraph(searchFrom->second.get(), nodeTo, wayLength); // if adjacency list already contain node add it to it parent
        if (searchTo == adjacencyList.end()) { // if adjacency list isn`t contain node to
#ifdef LABA
            int heuristicNumber = 0;
            std::cout << "set heuristic number for node \"" << nodeTo << "\": ";
            std::cin >> heuristicNumber;
            Graph* graphHead = new Graph(nodeTo, heuristicNumber);
#else
            Graph* graphHead = new Graph(nodeTo, abs((static_cast<int>(nodeTo) - static_cast<int>(finish))));
#endif
            adjacencyList.insert(std::pair<char, Graph*>(nodeTo, graphHead)); // add to adjacency list node to
        }
    }
#ifdef INFO
    printAdjacencyList(adjacencyList); // print adjacency list
#endif
    std::vector <Graph*> way; // will contain answer
    algorithmAStar(adjacencyList, start, finish, way); // AStar
#ifdef INFO
    std::cout << "answer: ";
#endif
    std::cout << start;
    for (int i = way.size() - 1; i != -1; --i)
        std::cout << way[i]->name;
    std::cout << std::endl;
    return 0;
}
