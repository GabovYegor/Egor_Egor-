#include <iostream>
#include <cmath>
#include <vector>

class Square{
private:
    int x;
    int y;
    int sideSize;    // геттеры сеттеры
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
    Row(){
        countElements = 0;
        DELETED = false;
    }
    Square square;
    class Row* down;
    class Element* elementsHEAD;
    unsigned countRows;
    unsigned countElements;
    bool DELETED;
};

class Column{
public:
    Column(){
        countElements = 0;
        DELETED = false;
    }
    class Column* right;
    Element* elementsHEAD;
    unsigned countElements;
    unsigned x;
    unsigned y;
    bool DELETED;
};

class Element{
public:
    class Element* down;
    class Element* right;
    Column* column;
    unsigned countElements;
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

void printMatrix(class Matrix matrix){
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
    if(row->countElements){
        row->countElements++;
        newElement->right = row->elementsHEAD->right;
        row->elementsHEAD->right = newElement;
    }

    if(column->countElements){
        column->countElements++;
        newElement->down = column->elementsHEAD->down;
        column->elementsHEAD->down = newElement;
    }
    if(!row->countElements){
        row->countElements++;
        row->elementsHEAD = new Element;
        row->elementsHEAD = newElement;
        newElement->right = newElement;
    }
    if(!column->countElements){
        column->countElements++;
        column->elementsHEAD = new Element;
        column->elementsHEAD = newElement;
        newElement->down = newElement;
    }
}

void createElements(class Matrix matrix){
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
    column2delete->DELETED = true;
}

void deleteRow(class Matrix& matrix, class Row*& row2delete){
    class Row* currentRow = matrix.rowPointer;
    do{
        currentRow = currentRow->down;
    }while(currentRow->down != row2delete);
    currentRow->down = currentRow->down->down;
    if(matrix.rowPointer == row2delete)
        matrix.rowPointer = matrix.rowPointer->down;
    row2delete->DELETED = true;
}

void insertColumn(class Matrix& matrix, std::vector<class Column*>& deletedColumns){
    for(unsigned i = 0; i < deletedColumns.size(); ++i){
        deletedColumns[i]->DELETED = false;
        deletedColumns[i]->right = matrix.columnPoiner->right;
        matrix.columnPoiner->right = deletedColumns[i];
    }
//    for(unsigned i = 0; i < deletedColumns.size(); ++i)
//        deletedColumns.pop_back();
}

void insertRow(class Matrix& matrix, std::vector<class Row*>& deletedRows){
    for(unsigned i = 0; i < deletedRows.size(); ++i){
        deletedRows[i]->DELETED = false;
        deletedRows[i]->down = matrix.rowPointer->down;
        matrix.rowPointer->down = deletedRows[i];
    }
//    for(unsigned i = 0; i < deletedRows.size(); ++i)
//        deletedRows.pop_back();
}

unsigned getSize(Element* elementHEAD){
    Element* currentElement = elementHEAD;
    unsigned count = 0;
    do{
       if(!currentElement->row->DELETED)
            ++count;
       currentElement = currentElement->down;
    }while(currentElement != elementHEAD);
    return count;
};

class Column* chooseMinimalColumn(class Matrix matrix, unsigned& maxCount){
    class Column* currentColumn = matrix.columnPoiner;
    class Column* minColumn = matrix.columnPoiner;
    do{
        if(currentColumn->DELETED){
            currentColumn = currentColumn->right;
            continue;
        }
        minColumn->countElements = getSize(minColumn->elementsHEAD);
        currentColumn->countElements = getSize(currentColumn->elementsHEAD);
        if(minColumn->countElements > currentColumn->countElements)
            minColumn = currentColumn;
        if(maxCount < currentColumn->countElements)
            maxCount = currentColumn->countElements;
        currentColumn = currentColumn->right;
    }while(currentColumn != matrix.columnPoiner);
    return minColumn;
}

void algorithmX(class Matrix matrix, std::vector <class Square> solution){
    unsigned countMax = 0;
    std::vector <class Column*> deletedColumns;
    std::vector <class Row*> deletedRows;
    class Column* minColumn = chooseMinimalColumn(matrix, countMax);
    std::cout << "MAX " << countMax << " MINCOLUMN" << minColumn->x << minColumn->y << std::endl;
    if(countMax == 1){
        for(int i = 0; i < solution.size(); ++i)
            std::cout << solution[i].getX() << solution[i].getY() << solution[i].getSideSize() << std::endl;
        std::cout << "END" << std::endl;
        return;
    }
    if(countMax == 0)
        exit(0);
    Element* elMainColumn = minColumn->elementsHEAD;
    do{
        solution.push_back(elMainColumn->row->square);
        Element* elMainRow = elMainColumn->row->elementsHEAD;
        do{
            if(elMainColumn->row->DELETED){
                elMainRow = elMainRow->right;
                continue;
            }
            Element* column = elMainRow->column->elementsHEAD;
            do{
                if(column->row != elMainRow->row && !column->row->DELETED){
                    std::cout << "DELETE ROW " << column->row->square.getX() << " " <<
                                 column->row->square.getY() << " " <<
                                 column->row->square.getSideSize() << std::endl;
                    deletedRows.push_back(column->row);
                    deleteRow(matrix, column->row);
                }
                column = column->down;
                if(column->row->DELETED)
                    continue;
            }while(column != elMainRow->column->elementsHEAD);
            if(column->column != minColumn && !column->column->DELETED){
                std::cout << "DELETE COLUMN " << column->column->x << " " << column->column->y << std::endl;
                deletedColumns.push_back(column->column);
                deleteColumn(matrix, column->column);
            }
            elMainRow = elMainRow->right;
            if(elMainRow->column->DELETED)
                continue;
        }while(elMainRow != elMainRow->row->elementsHEAD);
        if(!elMainRow->row->DELETED){
            deletedRows.push_back(elMainRow->row);
            std::cout << "DELETE MAIN ROW " << elMainRow->row->square.getX() << " " <<
                         elMainRow->row->square.getY() << " " <<
                         elMainRow->row->square.getSideSize() << std::endl;
            deleteRow(matrix, elMainRow->row);
        }
        std::cout << "DELETE MAIN COLUMN "
                  << minColumn->x << " " << minColumn->y << std::endl;
        deletedColumns.push_back(minColumn);
        deleteColumn(matrix, minColumn);
        std::cout << "AFTER FUNCTION" << std::endl;
        //printMatrix(matrix);
        algorithmX(matrix, solution);
        insertColumn(matrix, deletedColumns);
        insertRow(matrix, deletedRows);
        std::cout << "ВОССТАНОВЛЕННАЯ" << std::endl;
        //printMatrix(matrix);
        elMainColumn = elMainColumn->down;
        if(elMainColumn->row->DELETED)
            continue;
    }while(elMainColumn != minColumn->elementsHEAD);
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
    std::vector <class Square> solution;
    algorithmX(matrix, solution);
    return 0;
}











