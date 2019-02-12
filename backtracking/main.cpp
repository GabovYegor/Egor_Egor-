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

void algorithmX(std::vector <class MatrixElement> matrix,
    std::vector <std::vector <class MatrixElement>>& solutions, std::vector <class MatrixElement> prevSolution){
    std::vector <class MatrixElement> currentSolution;
    std::vector <class MatrixElement> afterDelete;
    for(size_t iteratorElement = 0; iteratorElement < matrix.size(); ++iteratorElement){
        for(size_t iteratorPoint = 0; iteratorPoint < matrix[iteratorElement].points.size(); ++iteratorPoint){
            for(size_t i = 0; i < matrix.size(); ++i)
                matrix[i].deleted = false;
            for(size_t i = 0; i < afterDelete.size(); ++i)
                afterDelete.pop_back();
            for(size_t i = 0; i < currentSolution.size(); ++i)
                currentSolution.pop_back();
           if(matrix[iteratorElement].points[iteratorPoint] == matrix[0].points[0]){
               if(matrix[iteratorElement].square.sideSize <= (matrix[0].mainSquareSide - 3) / 4)
                   return;
                currentSolution.push_back(matrix[iteratorElement]);
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
                if(checkRightMatrix(afterDelete)){
                    for(size_t i = 0; i < afterDelete.size(); ++i)
                        currentSolution.push_back(afterDelete[i]);
                    for(size_t i = 0; i < prevSolution.size(); ++i)
                        currentSolution.push_back(prevSolution[i]);
                    solutions.push_back(currentSolution);
                    continue;
                }
                for(size_t i = 0; i < prevSolution.size(); ++i)
                    currentSolution.push_back(prevSolution[i]);
                algorithmX(afterDelete, solutions, currentSolution);
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
    //printMatrix(matrix);
    algorithmX(matrix, solutions, currentSolution);
    int minSize = 99;
    int minI;
    for(size_t i = 0; i < solutions.size(); ++i){
        currentSolution = solutions[i];
        if(currentSolution.size() < minSize){
            minSize = currentSolution.size();
            minI = i;
        }
    }
    currentSolution = solutions[minI];
    //std::cout << "ALL: " << solutions.size() << std::endl;
    std::cout << currentSolution.size() << std::endl;
    for(int i = 0; i < currentSolution.size(); ++i){
        std::cout << currentSolution[i].square.x << " "
                  << currentSolution[i].square.y << " "
                  << currentSolution[i].square.sideSize << std::endl;
    }
    return 0;
}


