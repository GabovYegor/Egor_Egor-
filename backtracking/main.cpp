#include <iostream>
#include <cmath>
#include <vector>

class Square{
private:
    int x;
    int y;
    int sideSize;
public:
    void setX(const unsigned x){this->x = x;}
    void setY(const unsigned y){this->y = y;}
    void setSideSize(const unsigned sideSize){this->sideSize = sideSize;}
    unsigned getSideSize(){return sideSize;}
    unsigned getX(){return x;}
    unsigned getY(){return y;}
    Square(){}
    Square(int x, int y, int sideSize){
        this->x = x;
        this->y = y;
        this->sideSize = sideSize;
    }
};

class Row{
public:
    Square square;
    class Row* down;
    class Element* elementsHEAD = nullptr;
};

class Column{
public:
    class Column* right;
    Element* elementsHEAD = nullptr;
    unsigned x;
    unsigned y;
};

class Element{
public:
    class Element* down;
    class Element* right;
    Column* column;
    Row* row;
};

class Matrix{
public:
    Matrix(){
        rowPointer = nullptr;
        columnPoiner = nullptr;
    }
    class Row* rowPointer;
    class Column* columnPoiner;
};

void printMatrix(class Matrix& matrix){
    std::cout << "INFO ABOUT ROWS:::" << std::endl;
    class Row* currentRow = matrix.rowPointer;
    do{
        std::cout << currentRow->square.getX() << " " <<
                     currentRow->square.getY() << " " <<
                     currentRow->square.getSideSize() << std::endl;
        currentRow = currentRow->down;
    }while(currentRow != matrix.rowPointer);
    std::cout << "INFO ABOUT COLUMNS:::" << std::endl;
    class Column* currentColumn = matrix.columnPoiner;
    do{
        std::cout << currentColumn->x << " " << currentColumn->y << std::endl;
        currentColumn = currentColumn->right;
    }while(currentColumn != matrix.columnPoiner);
}

void createSquare(const unsigned mainSquareSize, std::vector <Square>& squares){
    for(unsigned iteratorSize = mainSquareSize - 1; iteratorSize > 0; --iteratorSize){ // плохо
        for(unsigned x = 0; x < mainSquareSize; ++x){
            for(unsigned y = 0; y < mainSquareSize; ++y){
                if(x + iteratorSize <= mainSquareSize && y + iteratorSize <= mainSquareSize){
                    squares.push_back(Square(x, y, iteratorSize));
                }
            }
        }
    }
}

void createRows(class Matrix& matrix, std::vector <class Square> squares){
    if(!matrix.rowPointer){
        class Row* tempRow = new class Row;
        tempRow->down = tempRow;
        tempRow->square = squares[0];
        matrix.rowPointer = tempRow;
    }

    for(unsigned i = 1; i < squares.size(); ++i){
        class Row* currentRow = matrix.rowPointer;
        do{
            currentRow = currentRow->down;
        }while(currentRow->down != matrix.rowPointer);
        class Row* newRow = new class Row;
        newRow->down = currentRow->down;
        currentRow->down = newRow;
        newRow->square = squares[i];
    }
}

void createColumn(class Matrix& matrix, unsigned mainSquareSide){
    if(!matrix.columnPoiner){
        class Column* tempColumn = new class Column;
        tempColumn->right = tempColumn;
        tempColumn->x = 0;
        tempColumn->y = 0;
        matrix.columnPoiner = tempColumn;
    }
    for(unsigned i = 1; i < pow(mainSquareSide, 2); ++i){
        class Column* currentColumn = matrix.columnPoiner;
        do{
            currentColumn = currentColumn->right;
        }while(currentColumn->right != matrix.columnPoiner);
        class Column* newColumn = new class Column;
        newColumn->right = currentColumn->right;
        currentColumn->right = newColumn;
        newColumn->x = i / mainSquareSide;
        newColumn->y = i % mainSquareSide;
    }
}

void insertElement(class Row*& row, class Column*& column){
    Element* newElement = new Element;
    newElement->column = column;
    newElement->row = row;
    if(row->elementsHEAD){
        newElement->right = row->elementsHEAD->right;
        row->elementsHEAD->right = newElement;
    }

    if(column->elementsHEAD){
        newElement->down = column->elementsHEAD->down;
        column->elementsHEAD->down = newElement;
    }
    if(!row->elementsHEAD){
        row->elementsHEAD = new Element;
        row->elementsHEAD = newElement;
        newElement->right = newElement;
    }
    if(!column->elementsHEAD){
        column->elementsHEAD = new Element;
        column->elementsHEAD = newElement;
        newElement->down = newElement;
    }
}

void createElements(class Matrix& matrix){
    class Row* currentRow = matrix.rowPointer;
    do{
        for(unsigned y = currentRow->square.getY(); y < currentRow->square.getY() + currentRow->square.getSideSize(); ++y){
            for(unsigned x = currentRow->square.getX(); x < currentRow->square.getX() + currentRow->square.getSideSize(); ++x){
                class Column* currentColumn = matrix.columnPoiner;
                do{
                    currentColumn = currentColumn->right;
                }while(currentColumn->x != x || currentColumn->y != y);
                insertElement(currentRow, currentColumn);
            }
        }
        currentRow = currentRow->down;
    }while(currentRow != matrix.rowPointer);
}

void deleteColumn(class Matrix& matrix, class Column*& column2delete){
    class Column* currentColumn = matrix.columnPoiner;
    do{
        currentColumn = currentColumn->right;
    }while(currentColumn->right != column2delete);
    currentColumn->right = currentColumn->right->right;
    if(matrix.columnPoiner == column2delete)
        matrix.columnPoiner = matrix.columnPoiner->right;
}

void deleteRow(class Matrix& matrix, class Row*& row2delete){
    class Row* currentRow = matrix.rowPointer;
    do{
        currentRow = currentRow->down;
    }while(currentRow->down != row2delete);
    currentRow->down = currentRow->down->down;
    if(matrix.rowPointer == row2delete)
        matrix.rowPointer = matrix.rowPointer->down;
}

void insertColumn(class Matrix& matrix, std::vector<class Column*>& deletedColumns){
    for(unsigned i = 0; i < deletedColumns.size(); ++i){
        deletedColumns[i]->right = matrix.columnPoiner->right;
        matrix.columnPoiner->right = deletedColumns[i];
    }
}

void insertRow(class Matrix& matrix, std::vector<class Row*>& deletedRows){
    for(unsigned i = 0; i < deletedRows.size(); ++i){
        deletedRows[i]->down = matrix.rowPointer->down;
        matrix.rowPointer->down = deletedRows[i];
    }
}

void chooseMinColumn(Matrix& matrix){
    Column* currentColumn = matrix.columnPoiner;
    Column* minColumn = nullptr;
    unsigned minColumnSize = 0;
    do{
        Element* currentElement = currentColumn->elementsHEAD;
        do{
            currentElement = currentElement->down;
        }while(currentElement != currentColumn->elementsHEAD);

        currentColumn = currentColumn->right;
    }while(currentColumn != matrix.columnPoiner);
}

void algorithmX(Matrix& matrix){
    // choose minimal column
}

int main(){
    unsigned mainSquareSize = 0;
    std::cin >> mainSquareSize;
    std::vector <Square> squares;
    createSquare(mainSquareSize, squares);
    class Matrix matrix;
    createRows(matrix, squares);
    createColumn(matrix, mainSquareSize);
    createElements(matrix);
    printMatrix(matrix);
    return 0;
}











