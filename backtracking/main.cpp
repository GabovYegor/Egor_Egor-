#include <iostream>
#include <cmath>
#include <vector>

class Square{
public:
    int x;
    int y;
    int sideSize;    // геттеры сеттеры
public:
    Square(){}
    Square(int x, int y, int sideSize){
        this->x = x;
        this->y = y;
        this->sideSize = sideSize;
    }
};

class Point{
public:
    int x;
    int y;
public:
    Point(){}
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    bool operator ==(class Point Point2){
        return Point2.x == x && Point2.y == y;
    }
};

class MatrixElement{
public:
    int mainSquareSide;
    std::vector <class Point> points; // геттеры сеттеры
    class Square square;
    bool deleted;
public:
    MatrixElement(class Square square, std::vector <class Point> masPoins, int mainSquareSide){
        points = masPoins;
        this->square = square;
        points = masPoins;
        this->mainSquareSide = mainSquareSide;
    }
};

std::vector <class MatrixElement> createMatrix(int mainSquareSize){
    std::vector <class MatrixElement> matrix;
    for(int iteratorSquareSize = mainSquareSize - 1; iteratorSquareSize > 0; --iteratorSquareSize){
        for(int iteratorX = 0; iteratorX < mainSquareSize; ++iteratorX){
            for(int iteratorY = 0; iteratorY < mainSquareSize; ++iteratorY){
                std::vector <class Point> masPoints;
                if(iteratorX + iteratorSquareSize <= mainSquareSize &&
                   iteratorY + iteratorSquareSize <= mainSquareSize){
                    for(int i = iteratorY; i < iteratorY + iteratorSquareSize; ++i){
                        for(int j = iteratorX; j < iteratorX + iteratorSquareSize; ++j){
                            masPoints.push_back(Point(i, j));
                        }
                    }
                    matrix.push_back(MatrixElement(Square(iteratorX, iteratorY, iteratorSquareSize), masPoints, mainSquareSize));
                }
            }
        }
    }
    return matrix;
}

void printMatrix(std::vector <class MatrixElement>& matrix){
    for(size_t i = 0; i < matrix.size(); ++i){
        std::cout << "size = " << matrix[i].square.sideSize << " x = " << matrix[i].square.x << " y = " << matrix[i].square.y << std::endl;
        for(size_t j = 0; j < matrix[i].points.size(); ++j){
            std::cout << "x = " << matrix[i].points[j].x << " y = " << matrix[i].points[j].y << std::endl;
        }
    }
}

bool checkRightMatrix(std::vector <class MatrixElement> matrix){
    if(matrix.size() == 0)
        return true;
    for(int y = 0; y < matrix[0].mainSquareSide; ++y){
        for(int x = 0; x < matrix[0].mainSquareSide; ++x){
            int countThisPoint = 0;
            for(size_t i = 0; i < matrix.size(); ++i){
                for(size_t j = 0; j < matrix[i].points.size(); ++j){
                    if(matrix[i].points[j] == Point(x, y))
                        ++countThisPoint;
                }
            }
            if(countThisPoint > 1)
                return false;
        }
    }
    return true;
}

bool inFirst = true;

void algorithmX(std::vector <class MatrixElement>& matrix,
    std::vector <std::vector <class MatrixElement>>& solutions, std::vector <class MatrixElement> currentSolution){
    std::vector <class MatrixElement> afterDelete;
//    std::cout << "INFUNCTION" << std::endl;
    size_t minSize = 999;
    for(size_t iteratorElement = 0; iteratorElement < matrix.size(); ++iteratorElement){
        for(size_t iteratorPoint = 0; iteratorPoint < matrix[iteratorElement].points.size(); ++iteratorPoint){
            for(size_t i = 0; i < matrix.size(); ++i)
                matrix[i].deleted = false;
            for(size_t i = 0; i < afterDelete.size(); ++i)
                            afterDelete.pop_back();
            if(matrix[iteratorElement].points[iteratorPoint] == matrix[0].points[0]){
                if(matrix[iteratorElement].square.sideSize < matrix[0].mainSquareSide / 2 && inFirst || matrix[iteratorElement].square.sideSize == 1){
                    inFirst = false;
                    return;
                }
                for(size_t solutionPoint = 0; solutionPoint < matrix[iteratorElement].points.size(); ++solutionPoint){
                    for(size_t i = 0; i < matrix.size(); ++i){
                        for(size_t j = 0; j < matrix[i].points.size(); ++j){
                            if(matrix[iteratorElement].points[solutionPoint] == matrix[i].points[j])
                                matrix[i].deleted = true;
                        }
                    }
                }
                for(size_t i = 0; i < matrix.size(); ++i){
                    if(!matrix[i].deleted)
                        afterDelete.push_back(matrix[i]);
                }
//                std::cout << "INSERT ELEMENT: " << matrix[iteratorElement].square.x << " "
//                          << matrix[iteratorElement].square.y << " "
//                          << matrix[iteratorElement].square.sideSize << std::endl;
//                for(size_t i = 0; i < afterDelete.size(); ++i){
//                    std::cout << afterDelete[i].square.x << " "
//                              << afterDelete[i].square.y << " "
//                              << afterDelete[i].square.sideSize << std::endl;
//                }
                if(checkRightMatrix(afterDelete)){
                    if(minSize < afterDelete.size())
                        continue;
                    if(afterDelete.size() < minSize)
                        minSize = afterDelete.size();
                    std::vector <class MatrixElement> thisSolution;
//                    std::cout << "RIGHT!!!!!!!!!!!!!!!" << std::endl;
//                    std::cout << matrix[iteratorElement].square.x << " "
//                              << matrix[iteratorElement].square.y << " "
//                              << matrix[iteratorElement].square.sideSize << std::endl;
                    thisSolution.push_back(matrix[iteratorElement]);
                    for(size_t i = 0; i < currentSolution.size(); ++i){
//                        std::cout << currentSolution[i].square.x << " "
//                                  << currentSolution[i].square.y << " "
//                                  << currentSolution[i].square.sideSize << std::endl;
                        thisSolution.push_back(currentSolution[i]);
                    }
                    for(size_t i = 0; i < afterDelete.size(); ++i){
//                        std::cout << afterDelete[i].square.x << " "
//                                  << afterDelete[i].square.y << " "
//                                  << afterDelete[i].square.sideSize << std::endl;
                        thisSolution.push_back(afterDelete[i]);
                    }
                    solutions.push_back(thisSolution);
                    continue;
                }
                currentSolution.push_back(matrix[iteratorElement]);
                algorithmX(afterDelete, solutions, currentSolution);
                currentSolution.pop_back();
            }
        }
    }
    return;
}

int main(){
    int mainSquareSize = 0;
    std::cin >> mainSquareSize;
    std::vector <class MatrixElement> matrix;
    std::vector <std::vector <class MatrixElement>> solutions;
    std::vector <class MatrixElement> currentSolution;
    matrix = createMatrix(mainSquareSize);
    algorithmX(matrix, solutions, currentSolution);
//    for(size_t i = 0; i < solutions.size(); ++i){
//        std::cout << "------------------" << std::endl;
//        for(size_t j = 0; j < solutions[i].size(); ++j){
//            std::cout << solutions[i][j].square.x << " "
//                      << solutions[i][j].square.y << " "
//                      << solutions[i][j].square.sideSize << std::endl;
//        }
//    }
    int minSize = 999;
    int minI = 0;
    for(size_t i = 0; i < solutions.size(); ++i){
        if(minSize > solutions[i].size()){
            minI = i;
            minSize = solutions[i].size();
        }
    }
    std::cout << minSize << std::endl;
    for(size_t i = 0; i < solutions[minI].size(); ++i){
        std::cout << solutions[minI][i].square.x << " "
                  << solutions[minI][i].square.y << " "
                  << solutions[minI][i].square.sideSize << std::endl;
    }

    return 0;
}




















