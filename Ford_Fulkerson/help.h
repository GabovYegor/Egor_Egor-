#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

class Node{
public:
    int flow;
    int name;
    bool isVisited;
};

class GraphMatrix{
public:
    std::vector <std::vector <std::shared_ptr <Node>>> matrix;
    std::map <char, int> translator;
public:
    GraphMatrix(int countEdge = 0){
        matrix.resize(countEdge);
        for(int i = 0; i < countEdge; ++i){
            matrix[i].resize(countEdge);
            for(int j = 0; j < countEdge; ++j)
                matrix[i][j] = std::make_shared<Node>();
        }
    }

    void cutOffMatrix(int newSize){
        matrix.resize(newSize);
        for(int i = 0; i < newSize; ++i)
            matrix[i].resize(newSize);
    }

    void createMatrix(int countEdge){
        int mapNum = 0;
        for(int i = 0; i < countEdge; ++i){
            char tempNodeFrom, tempNodeTo;
            int tempFlowNumber;
            std::cin >> tempNodeFrom >> tempNodeTo >> tempFlowNumber;
            if(translator.find(tempNodeFrom) == translator.end()){
                translator.insert(std::pair <char, int> (tempNodeFrom, mapNum));
                 ++mapNum;
            }
            if(translator.find(tempNodeTo) == translator.end()){
                translator.insert(std::pair <char, int> (tempNodeTo, mapNum));
                ++mapNum;
            }
            matrix[translator.find(tempNodeFrom)->second][translator.find(tempNodeTo)->second]->flow = tempFlowNumber;
        }
        cutOffMatrix(mapNum);
        for(size_t i = 0; i < matrix.size(); ++i){
            for(size_t j = 0; j < matrix[i].size(); ++j)
                matrix[i][j].get()->name = j;
        }
    }
    friend std::ostream& operator<< (std::ostream& out, GraphMatrix& graph);
};

char convertMap(std::map <char, int>& tranlator, int target){
    for(auto it: tranlator)
        if(it.second == target)
            return it.first;
    return '\0';
}

std::ostream& operator<< (std::ostream& out, GraphMatrix& graph){
    std::cout << "  ";
    for(size_t i = 0; i < graph.matrix.size(); ++i)
        std::cout << convertMap(graph.translator, i) << " ";
    std::cout << std::endl;
    for(size_t i = 0; i < graph.matrix.size(); ++i){
        std::cout << convertMap(graph.translator, i) << " ";
        for(size_t j = 0; j < graph.matrix[i].size(); ++j){
            std::cout << graph.matrix[i][j]->flow << " ";
        }
        out << std::endl;
    }
    return out;
}

void algorithmFordFulkerson(GraphMatrix& graph, char start, char finish){
    int graphStart = graph.translator.find(start)->second;
    int graphFinish = graph.translator.find(finish)->second;
    std::vector <int> neighborhoods;
    std::vector <int> flowQueue;
    std::vector <int> way;
    // не просчитываются тупики и вообще это только для одной итерации
    // в некоторых местах вместо можно вызывать функцию convertMap

    // вспомнить про isVisited
    while(graphStart != graphFinish){
        neighborhoods.clear();
        for(size_t i = 0; i < graph.matrix.size(); ++i){
            if(graph.matrix[graphStart][i].get()->flow && !graph.matrix[graphStart][i].get()->isVisited)
                neighborhoods.push_back(i);
        }
        if(!neighborhoods.size()){
            if(graphStart == graph.translator.find(start)->second){
                std::cout << "there are no ways from start" << std::endl;
                return;
            }
            std::cout << "return to element: " << way[way.size() - 1] << " - there are no way" << std::endl;
            graph.matrix[way[way.size() - 1]][graphStart].get()->isVisited = true;
            graphStart = way[way.size() - 1];
            way.pop_back();
            continue;
        }
        std::cout << " neighborhoods " << graphStart << ": ";
        for(auto it: neighborhoods){
            std::cout << "(" << it << ";" << graph.matrix[graphStart][it].get()->flow << "), ";
        }
        std::cout << std::endl;
        int maxFlow = -999;
        int maxFlowElement = 0;
        for(size_t i = 0; i < neighborhoods.size(); ++i){
            if(graph.matrix[graphStart][neighborhoods[i]].get()->flow > maxFlow){
                maxFlow = graph.matrix[graphStart][neighborhoods[i]].get()->flow;
                maxFlowElement = i;
            }
        }
        std::cout << "Best: (" << neighborhoods[maxFlowElement] << "; " << maxFlow << "), " << std::endl;
        flowQueue.push_back(maxFlow);
        way.push_back(graphStart);
        graph.matrix[graphStart][neighborhoods[maxFlowElement]].get()->isVisited = true;
        graphStart = graph.matrix[graphStart][neighborhoods[maxFlowElement]].get()->name;
    }
    std::cout << "queue of flows: " << std::endl;
    int minFlow = 999999;
    for(auto it: flowQueue){
        if(it < minFlow)
            minFlow = it;
        std::cout << it;
    }
    std::cout << std::endl << "min flow: " << minFlow << std::endl;
    std::cout << "way: ";
    for(auto it: way)
        std::cout << it << " ";
    std::cout << graphStart << std::endl;
    for(int i = way.size() - 1; i != -1; --i){
        std::cout << graph.matrix[way[i]][graphStart].get()->flow << " ";
        graph.matrix[way[i]][graphStart].get()->flow -= minFlow;
        graph.matrix[graphStart][way[i]].get()->flow += minFlow;
        graphStart = way[i];
    }
    std::cout << "recount some flows" << std::endl;
    std::cout << graph;
}

int main(){
    int countEdge = 0;
    char start, finish;
    std::cin >> countEdge;
    std::cin >> start >> finish;
    GraphMatrix graph(countEdge * 2);
    graph.createMatrix(countEdge);
    std::cout << graph;
    algorithmFordFulkerson(graph, start, finish);
    std::cout << "Graph after algorithm: " << std::endl << graph;
    return 0;
}
