#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>

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
    bool isDeleted;
};

class Column{
public:
    class Column* right;
    Element* elementsHEAD = nullptr;
    unsigned x;
    unsigned y;
    bool isDeleted;
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
    if(column2delete->isDeleted == true){
        std::cout << "Column is already deleted" << std::endl;
        return;
    }
    if(matrix.columnPoiner == column2delete && matrix.columnPoiner == matrix.columnPoiner->right){
        std::cout << "matrix.columnPointer is Empty" << std::endl;
        matrix.columnPoiner = nullptr;
        return;
    }
    class Column* currentColumn = matrix.columnPoiner;
    column2delete->isDeleted = true;
    do{
        currentColumn = currentColumn->right;
    }while(currentColumn->right != column2delete);
    currentColumn->right = currentColumn->right->right;
    if(matrix.columnPoiner == column2delete)
        matrix.columnPoiner = matrix.columnPoiner->right;
}

void deleteRow(class Matrix& matrix, class Row*& row2delete){
    if(row2delete->isDeleted == true){
        std::cout << "Row is already deleted" << std::endl;
        return;
    }
    if(matrix.rowPointer == row2delete && matrix.rowPointer == matrix.rowPointer->down){
        std::cout << "matrix.rowPoiner is Empty" << std::endl;
        matrix.rowPointer = nullptr;
        return;
    }
    class Row* currentRow = matrix.rowPointer;
    row2delete->isDeleted = true;
    do{
        currentRow = currentRow->down; // проблема
    }while(currentRow->down != row2delete);
    currentRow->down = currentRow->down->down;
    if(matrix.rowPointer == row2delete)
        matrix.rowPointer = matrix.rowPointer->down;
}

void insertColumn(class Matrix& matrix, std::vector<class Column*>& deletedColumns){
    std::cout << "COLUMN" << std::endl;
    if(!matrix.columnPoiner){
        deletedColumns[0]->isDeleted = false;
        matrix.columnPoiner = deletedColumns[0];
        deletedColumns[0]->right = deletedColumns[0];
        for(unsigned i = 1; i < deletedColumns.size(); ++i){
            deletedColumns[i]->isDeleted = false;
            deletedColumns[i]->right = matrix.columnPoiner->right;
            matrix.columnPoiner->right = deletedColumns[i];
        }
        return;
    }
    for(unsigned i = 0; i < deletedColumns.size(); ++i){
        deletedColumns[i]->isDeleted = false;
        deletedColumns[i]->right = matrix.columnPoiner->right;
        matrix.columnPoiner->right = deletedColumns[i];
    }
    deletedColumns.clear();
}

void insertRow(class Matrix& matrix, std::vector<class Row*>& deletedRows){
    std::cout << "ROW" << std::endl;
    if(!matrix.rowPointer){
        deletedRows[0]->isDeleted = false;
        matrix.rowPointer = deletedRows[0];
        deletedRows[0] = deletedRows[0]->down;
        for(unsigned i = 1; i < deletedRows.size(); ++i){
            deletedRows[i]->isDeleted = false;
            deletedRows[i]->down = matrix.rowPointer->down;
            matrix.rowPointer->down = deletedRows[i];
        }
        return;
    }
    for(unsigned i = 0; i < deletedRows.size(); ++i){
        deletedRows[i]->isDeleted = false;
        deletedRows[i]->down = matrix.rowPointer->down;
        matrix.rowPointer->down = deletedRows[i];
    }
    deletedRows.clear();
}

Column* chooseMinColumn(Matrix& matrix, unsigned& maxColumnSize){
    int minColumnSize = -1;
    Column* currentColumn = matrix.columnPoiner;
    Column* minColumn = nullptr;
    if(!matrix.columnPoiner)
        return nullptr;
    do{
        if(currentColumn->isDeleted){
            currentColumn = currentColumn->right;
            continue;
        }

        Element* currentElement = currentColumn->elementsHEAD;
        unsigned currentColumnSize = 0;
        do{
            if(!currentElement->row->isDeleted){
                currentColumnSize++;
            }
            currentElement = currentElement->down;
        }while(currentElement != currentColumn->elementsHEAD);
        if(minColumnSize > currentColumnSize){
            minColumn = currentColumn;
            minColumnSize = currentColumnSize;
        }
        if(maxColumnSize < currentColumnSize)
            maxColumnSize = currentColumnSize;
        currentColumn = currentColumn->right;
    }while(currentColumn != matrix.columnPoiner);
    std::cout << maxColumnSize << std::endl; // input 0 => minColumn = nullptr и падает
    return minColumn;
}

void algorithmX(Matrix& matrix){
    std::vector<class Column*> deletedColumns;
    std::vector<class Row*> deletedRows;
    unsigned maxColumnSize = 0;
    Column* minColumn = chooseMinColumn(matrix, maxColumnSize);
    if(!minColumn){
        std::cout << "END" << std::endl;
        return;
    }
    std::cout << "min Column: " << minColumn->x << " " << minColumn->y << " SIZE: " << maxColumnSize << std::endl;
    if(maxColumnSize == 1)
        return;
    Element* currentColumnElement = minColumn->elementsHEAD;
    do{
        Element* currentRowElement = currentColumnElement->row->elementsHEAD;
        if(currentColumnElement->row->isDeleted){
            currentColumnElement = currentColumnElement->down;
            continue;
        }
        do{
            Element* currentDeleteColumn = currentRowElement->column->elementsHEAD;
            if(currentRowElement->column->isDeleted){
                currentRowElement = currentRowElement->right;
                continue;
            }
            do{
                if(!currentDeleteColumn->row->isDeleted && currentDeleteColumn->row != currentRowElement->row){
                    std::cout << "delete Row: " << currentDeleteColumn->row->square.getX() << " " <<
                                 currentDeleteColumn->row->square.getY() << " " <<
                                 currentDeleteColumn->row->square.getSideSize() << std::endl;
                    deletedRows.push_back(currentDeleteColumn->row);
                    std::cout << "s" << std::endl;
                    deleteRow(matrix, currentDeleteColumn->row);
                    std::cout << "s" << std::endl;
                }
                currentDeleteColumn = currentDeleteColumn->down;
            }while(currentDeleteColumn != currentRowElement->column->elementsHEAD);
            if(currentRowElement->column != minColumn){
                std::cout << "delete Column: " << currentRowElement->column->x << " " << currentRowElement->column->y << std::endl;
                deletedColumns.push_back(currentRowElement->column);
                deleteColumn(matrix, currentRowElement->column);
            }
            currentRowElement = currentRowElement->right;
        }while(currentRowElement != currentColumnElement->row->elementsHEAD);
        std::cout << "delete mainRow: " << currentColumnElement->row->square.getX() << " " <<
                     currentColumnElement->row->square.getY() << " " <<
                     currentColumnElement->row->square.getSideSize() << std::endl;
        deletedRows.push_back(currentColumnElement->row);
        deleteRow(matrix, currentColumnElement->row);
        std::cout << "delete mainColumn: " << minColumn->x << " " << minColumn->y << std::endl;
        deletedColumns.push_back(minColumn);
        deleteColumn(matrix, minColumn);
        std::cout << "Матрица после функции: " << std::endl;
        //printMatrix(matrix);
        algorithmX(matrix);
        insertColumn(matrix, deletedColumns);
        insertRow(matrix, deletedRows);
        for(int i = 0 ; i < deletedRows.size(); ++i){
            std::cout << deletedRows[i]->square.getX() << " "
                      << deletedRows[i]->square.getY() << " "
                      << deletedRows[i]->square.getSideSize() << std::endl;
        }
        std::cout << "Восстановленная матрица" << std::endl;
        //printMatrix(matrix);
        std::cout << "NEXT" << std::endl;
        currentColumnElement = currentColumnElement->down;
        if(currentColumnElement == minColumn->elementsHEAD)
            std::cout << "PIZDA" << std::endl;
    }while(currentColumnElement != minColumn->elementsHEAD);
}

int main(){
    unsigned mainSquareSize = 0;
    std::cin >> mainSquareSize;
    std::vector <Square> squares;
    class Matrix matrix;
    createSquare(mainSquareSize, squares);
    createRows(matrix, squares);
    createColumn(matrix, mainSquareSize);
    createElements(matrix);
    printMatrix(matrix);
    algorithmX(matrix);
    return 0;
}











