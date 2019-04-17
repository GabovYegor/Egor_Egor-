#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iomanip>

#define INFO

// class for store node data
class Node {
public:
    int flow;
    int name;
    bool isVisited;
};

// class of graph, based on matrix
class GraphMatrix {
public:
    std::vector <std::vector <std::shared_ptr <Node>>> matrix;
    std::map <char, int> translator;
public:
    GraphMatrix(int countEdge = 0) {
        matrix.resize(countEdge);
        for (int i = 0; i < countEdge; ++i) {
            matrix[i].resize(countEdge);
            for (int j = 0; j < countEdge; ++j)
                matrix[i][j] = std::make_shared<Node>(); // make_shared safer if will be exception
        }
    }

    // copy constuctor
    GraphMatrix(GraphMatrix& other) : GraphMatrix(other.matrix.size()) {
        translator = other.translator;
        for (size_t i = 0; i < other.matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                matrix[i][j].get()->flow = other.matrix[i][j].get()->flow;
                matrix[i][j].get()->isVisited = other.matrix[i][j].get()->isVisited;
                matrix[i][j].get()->name = other.matrix[i][j].get()->name;
            }
        }
    }

    // resize matrix size
    void cutOffMatrix(int newSize) {
        matrix.resize(newSize);
        for (int i = 0; i < newSize; ++i)
            matrix[i].resize(newSize);
    }

    // create matrix
    std::vector <std::pair <char, char>> createMatrix(int countEdge) {
        std::vector <std::pair <char, char>> all_edges; // massive of all edged need for task - not for algorithm
        int mapNum = 0;
        for (int i = 0; i < countEdge; ++i) {
            char tempNodeFrom, tempNodeTo;
            int tempFlowNumber;
            std::cin >> tempNodeFrom >> tempNodeTo >> tempFlowNumber; // set from and to value
            all_edges.push_back(std::pair <char, char>(tempNodeFrom, tempNodeTo));
            if (translator.find(tempNodeFrom) == translator.end()) {
                translator.insert(std::pair <char, int>(tempNodeFrom, mapNum)); // tranlate char to int
                ++mapNum;
            }
            if (translator.find(tempNodeTo) == translator.end()) {
                translator.insert(std::pair <char, int>(tempNodeTo, mapNum)); // tranlate char to int
                ++mapNum;
            }
            matrix[translator.find(tempNodeFrom)->second][translator.find(tempNodeTo)->second]->flow = tempFlowNumber; // set matrix value
        }
        cutOffMatrix(mapNum); // cut off matrix size
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) { // for istock node
                matrix[i][j].get()->name = j;
                if (!j)
                    matrix[i][j].get()->isVisited = true;
            }
        }
        return all_edges;
    }

    // override operator -= by difference between flows
    GraphMatrix& operator -=(GraphMatrix& other) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                matrix[i][j].get()->flow -= other.matrix[i][j].get()->flow;
            }
        }
        return *this;
    }
    friend std::ostream& operator<< (std::ostream&, GraphMatrix&);
};

// return translate of int value
char convertMap(std::map <char, int>& tranlator, int target) {
    for (auto it : tranlator)
        if (it.second == target)
            return it.first;
    return '\0'; // RVO work?
}

// print matrix data
std::ostream& operator<< (std::ostream& out, GraphMatrix& graph) {
    std::cout << "    ";
    for (size_t i = 0; i < graph.matrix.size(); ++i)
        std::cout << convertMap(graph.translator, i) << "   ";
    std::cout << std::endl;
    for (size_t i = 0; i < graph.matrix.size(); ++i) {
        std::cout << convertMap(graph.translator, i) << " ";
        for (size_t j = 0; j < graph.matrix[i].size(); ++j) {
            std::cout << std::setw(3) << graph.matrix[i][j]->flow << " ";
        }
        out << std::endl;
    }
    return out;
}

// main algorithm Ford-Falkerson
int algorithmFordFulkerson(GraphMatrix& graph, const char& start, const char& finish) {
    int graphStart = graph.translator.find(start)->second;
    int graphFinish = graph.translator.find(finish)->second;
    std::vector <int> neighborhoods;
    std::vector <int> flowQueue;
    std::vector <int> way;
    int resultMaxFlow = 0;
    while (true) {
        graphStart = graph.translator.find(start)->second;
        way.clear();          // null data
        flowQueue.clear();    // null data
        while (graphStart != graphFinish) { // while don`t achive stock
            neighborhoods.clear();
            for (size_t i = 0; i < graph.matrix.size(); ++i) {
                if (graph.matrix[graphStart][i].get()->flow && !graph.matrix[graphStart][i].get()->isVisited) // find neighborhoods
                    neighborhoods.push_back(i);
            }
            if (!neighborhoods.size()) {
                if (graphStart == graph.translator.find(start)->second) {
#ifdef INFO
                    std::cout << "there are no ways from start - end of algorithm" << std::endl << "max flow throught graph: ";
#endif
                    return resultMaxFlow; // end - from istok we cant go in any place
                }
#ifdef INFO
                std::cout << "return to element: " << convertMap(graph.translator, way[way.size() - 1]) << " - there are no way" << std::endl;
#endif
                graph.matrix[way[way.size() - 1]][graphStart].get()->isVisited = true;
                graphStart = way[way.size() - 1];
                way.pop_back();
                continue;
            }
#ifdef INFO
            std::cout << "neighborhoods " << convertMap(graph.translator, graphStart) << ": ";
            for (auto it : neighborhoods) {
                std::cout << "(" << convertMap(graph.translator, it) << ";" << graph.matrix[graphStart][it].get()->flow << "), ";
            }
            std::cout << std::endl;
#endif
            int maxFlow = -999999;
            int maxFlowElement = 0;
            // find max flow from neighborhoods
            for (size_t i = 0; i < neighborhoods.size(); ++i) {
                if (graph.matrix[graphStart][neighborhoods[i]].get()->flow > maxFlow) {
                    maxFlow = graph.matrix[graphStart][neighborhoods[i]].get()->flow;
                    maxFlowElement = i;
                }
            }
#ifdef INFO
            std::cout << "Best: (" << convertMap(graph.translator, neighborhoods[maxFlowElement]) << "; " << maxFlow << "), ";
#endif
            flowQueue.push_back(maxFlow);
            way.push_back(graphStart);
            graph.matrix[graphStart][neighborhoods[maxFlowElement]].get()->isVisited = true;
            graphStart = graph.matrix[graphStart][neighborhoods[maxFlowElement]].get()->name;
        }
#ifdef INFO
        std::cout << " - it`s finish point" << std::endl;
        std::cout << "queue of flows: ";
#endif
        // find min flow from way
        int minFlow = 999999;
        for (auto it : flowQueue) {
            if (it < minFlow)
                minFlow = it;
#ifdef INFO
            std::cout << it << " ";
#endif
        }
        // add result flow current flow
        resultMaxFlow += minFlow;
#ifdef INFO
        std::cout << std::endl << "min flow: " << minFlow << std::endl;
        std::cout << "way: ";
        for (auto it : way)
            std::cout << convertMap(graph.translator, it) << " ";
        std::cout << convertMap(graph.translator, graphStart) << std::endl;
#endif
        // recount some edges from way
        for (int i = way.size() - 1; i != -1; --i) {
            graph.matrix[way[i]][graphStart].get()->isVisited = false;
            graph.matrix[way[i]][graphStart].get()->flow -= minFlow;
            graph.matrix[graphStart][way[i]].get()->flow += minFlow;
            graphStart = way[i];
        }
#ifdef INFO
        std::cout << "recount some flows" << std::endl;
        std::cout << graph;
#endif
    }
}

int main() {
    int countEdge = 0;
    char start, finish;
    std::cin >> countEdge;
    std::cin >> start >> finish;
    GraphMatrix graph(countEdge * 2); // our matrix
    std::vector <std::pair <char, char>> all_edges = graph.createMatrix(countEdge); // for task
    GraphMatrix originalGraph(graph); // safed graph data for future
#ifdef INFO
    std::cout << graph;
#endif
    std::cout << algorithmFordFulkerson(graph, start, finish) << std::endl;
#ifdef INFO
    std::cout << "Graph after algorithm: " << std::endl << graph;
#endif
    originalGraph -= graph; // set edges values
#ifdef INFO
    std::cout << "original graph - graph after function:" << std::endl;
    std::cout << originalGraph;
#endif
    // sort for stepic tast; used lamda expression
    std::sort(all_edges.begin(), all_edges.end(),
              [](const std::pair <char, char>& a, const std::pair <char, char>& b)->bool {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first < b.first;
    });
    for (size_t i = 0; i < all_edges.size(); ++i) {
        graph.translator.find(all_edges[i].second)->second;
        std::cout << all_edges[i].first << " " << all_edges[i].second << " "
                  << originalGraph.matrix[graph.translator.find(all_edges[i].first)->second]
                     [graph.translator.find(all_edges[i].second)->second].get()->flow << std::endl;
    }
    return 0;
}
