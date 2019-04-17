#include <iostream>
#include <vector>
#include <cmath>

#define INFO

// Печатает содержимое Table.
void printTable(const std::vector<std::vector<int>>& Table, int squareSize, int deep){
    for(int i = 0; i < squareSize; ++i){
        for(int k = 0; k < deep; ++k)
            std::cout << "       ";
        for(int j = 0; j < squareSize; ++j)
            std::cout << Table[i][j] << " ";
        std::cout << std::endl;
    }
}

void removePart(std::vector<std::vector<int>>& Table, int squareSize, int x, int y, int partNumber){ // удалить часть
    for(int i = y; i < squareSize && Table[i][x] == partNumber; ++i)
        for (int j = x; j < squareSize && Table[i][j] == partNumber; ++j)
            Table[i][j] = 0;
}

bool setPart(std::vector<std::vector<int>>& Table, int squareSize, int x, int y, int currentSquareSize, int partNumber){
    if(currentSquareSize > squareSize - x || currentSquareSize > squareSize - y) // установить часть
        return false;
    for(int i = 0; i < currentSquareSize; ++i)
        for(int j = 0; j < currentSquareSize; ++j)
            if(!Table[y+i][x+j])
                Table[y+i][x+j]=partNumber;
            else{
                removePart(Table, squareSize, x, y, partNumber);
                return false;
            }
    return true;
}

bool findFreeCell(std::vector<std::vector<int>>& table, const int& squareSize, int& x, int& y){ // ищем свободную клетку
    for(int i = 0; i < squareSize; ++i)
        for(int j = 0; j < squareSize; ++j)
            if(!table[i][j]){
                x = j;
                y = i;
                return true;
            }
    return false;
}

void buildPrime(std::vector<std::vector<int>>& table, int squareSize, int x, int y, std::vector<std::vector<int>>& bestTable,
                                                     int partNmbr, int& bestPartNmbr, int deep){ // построение наилучшего решения
    if(partNmbr > bestPartNmbr) // есть вариант получше
        return;
    if (findFreeCell(table, squareSize, x, y)){ // if x,y free cell
        for (int iteratorSize = squareSize - 1; iteratorSize > 0; --iteratorSize){
            if(setPart(table, squareSize, x, y, iteratorSize, partNmbr)){ // То пробуем для нее различные размеры детали
                #ifdef INFO
                    //std::cout << "Part is set" << std::endl;
                    std::cout << "Free point: " << x + 1 << " " << y + 1 << std::endl;
                    printTable(table, squareSize, deep);
                    std::cout << std::endl;
                #endif
                buildPrime(table, squareSize, x, y, bestTable, partNmbr + 1, bestPartNmbr, deep+1); // И для каждого размера детали проходимся по остальным клеткам
            }
            removePart(table, squareSize, x, y, partNmbr);
        }
    }
    else if ((partNmbr - 1) < bestPartNmbr){
        bestPartNmbr = partNmbr - 1; // partNmbr не удалось поставить
        bestTable = table;
    }
}

void printParts(std::vector<std::vector<int>>& table, int squareSize, int partNmbr){ // вывод решения
    #ifdef INFO
    std::cout << "Solution table:" << std::endl;
        printTable(table, squareSize, 0);
    #endif
    for(int iterPartNbr = 1; iterPartNbr <= partNmbr; ++iterPartNbr){
        bool isFind = false;
        int i, j;
        for(i = 0; i < squareSize; ++i){
            for(j = 0; j < squareSize; ++j){
                if(table[i][j] == iterPartNbr){
                    std::cout << j + 1 << " " << i + 1 << " ";
                    isFind = true;
                    break;
                }
            }
            if(isFind)
                break;
        }
        int size = 0;
        for(;table[i][j] == iterPartNbr; ++j, ++size);
        std::cout << size << std::endl;
    }
}


int main(){
    int squareSize;
    std::cin >> squareSize;
    if(squareSize % 2 ==0){
        std::cout << 4 << std::endl;
        std::cout << 1       << " " << 1     << " " << squareSize / 2 << std::endl;
        std::cout << 1       << " " << squareSize / 2 + 1 << " " << squareSize / 2 << std::endl;
        std::cout << squareSize / 2+1   << " " << 1     << " " << squareSize / 2 << std::endl;
        std::cout << squareSize / 2+1   << " " << squareSize / 2 + 1 << " " << squareSize / 2 << std::endl;
        return 0;
    }
    if(squareSize % 3 == 0){
        int param = squareSize / 3; // зависит от стороны квадрата
        std::cout << 6 << std::endl;
        std::cout << 1       << " " << 1     << " " << 2  * param << std::endl;
        std::cout << 2 * param + 1   << " " << 1     << " " << param   << std::endl;
        std::cout << 2 * param + 1   << " " << param + 1   << " " << param   << std::endl;
        std::cout << 2 * param + 1   << " " << 2 * param + 1 << " " << param   << std::endl;
        std::cout << param + 1     << " " << 2 * param + 1 << " " << param   << std::endl;
        std::cout << 1       << " " << 2 * param + 1 << " " << param   << std::endl;
        return 0;
    }
    if(squareSize % 5 ==0){
        int param = squareSize / 5; // зависит от стороны квадрата
        std::cout << 8 << std::endl;
        std::cout << 1       << " " << 1     << " " << 3 * param << std::endl;
        std::cout << 1 + 3 * param   << " " << 1     << " " << 2 * param << std::endl;
        std::cout << 1 + 3 * param   << " " << 1 + 2 * param << " " << 2 * param << std::endl;
        std::cout << 1       << " " << 1 + 3 * param << " " << 2 * param << std::endl;
        std::cout << 1 + 2 * param   << " " << 1 + 3 * param << " " << param   << std::endl;
        std::cout << 1 + 2 * param   << " " << 1 + 4 * param << " " << param   << std::endl;
        std::cout << 1 + 3 * param   << " " << 1 + 4 * param << " " << param   << std::endl;
        std::cout << 1 + 4 * param   << " " << 1 + 4 *param << " " << param   << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> table(squareSize, std::vector<int>(squareSize, 0)); // Инициализировали массив NxN нулями
    std::vector<std::vector<int>> solution(squareSize, std::vector<int>(squareSize));
    setPart(table, squareSize, 0, 0, squareSize / 2 + 1, 1);
    setPart(table, squareSize, squareSize / 2 + 1, 0, squareSize / 2, 2);
    setPart(table, squareSize, 0, squareSize / 2 + 1, squareSize / 2, 3);
    setPart(table, squareSize, squareSize / 2 + 1, squareSize / 2, 1, 4);
    int countParts = 999;
    buildPrime(table, squareSize, squareSize / 2 + 2, squareSize / 2, solution, 5, countParts, 0);
    std::cout << countParts << std::endl;
    printParts(solution, squareSize, countParts);
    return 0;
}
