#include <iostream>
#include <cmath>
#include <vector>

typedef class Square{
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
}Square;

typedef class Row{
public:
    Row(){countElements = 0;}
    Square square;
    class Row* up;
    class Row* down;
    class Element* elementsHEAD;
    unsigned countElements;
    unsigned rowNumder;
    bool DELETED;
}Row;

typedef class Column{
public:
    Column(){countElements = 0;}
    class Column* left;
    class Column* right;
    unsigned countElements;
    Element* elementsHEAD;
    unsigned x;
    unsigned y;
    unsigned columnNumber;
    bool DELETED;
}Column;

typedef class Element{
public:
    class Element* up;
    class Element* down;
    class Element* left;
    class Element* right;
    Column* column;
    Row* row;
}Element;

void countRows(const unsigned mainSquareSize, std::vector <Square>& squares){
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

void printRows(Row** rows){
    Row* currentRow = *rows;
    do{
        std::cout << " X = " << currentRow->square.getX()
                  << " Y = " << currentRow->square.getY()
                  << " sizeSide " << currentRow->square.getSideSize()
                  << "   " << currentRow->rowNumder;
        if(currentRow->DELETED)
            std::cout << " DELETED" << std::endl;
        else
            std::cout << " DONT DELETED" << std::endl;
        currentRow = currentRow->down;
    }while(currentRow != *rows);
}

void printColumns(Column** columns){
    Column* currentColumn = *columns;
    do{
        std::cout << " COLUMN X =  " << currentColumn->x
                  << " COLUMN Y =  " << currentColumn->y
                  << " COLUMN NUMBER " << currentColumn->columnNumber;
        if(currentColumn->DELETED)
                    std::cout << " DELETED" << std::endl;
                else
                    std::cout << " DONT DELETED" << std::endl;
        currentColumn = currentColumn->right;
    }while(currentColumn != *columns);
}

void createRows(Row**& rows, std::vector <Square>& squares){
    rows = new Row*[squares.size()];
    Row* firstRow = new Row;
    *rows = firstRow;
    Row* lastRow = new Row;
    firstRow->up = lastRow;
    firstRow->down = lastRow;
    lastRow->up = firstRow;
    lastRow->down = firstRow;
    firstRow->square = squares[0];
    firstRow->rowNumder = 0;
    lastRow->square = squares[squares.size()-1];
    lastRow->rowNumder = squares.size() - 1;
    for(unsigned i = 1; i < squares.size() - 1; ++i){
        Row* newRow = new Row;
        newRow->down = lastRow;
        newRow->up = lastRow->up;
        lastRow->up->down = newRow;
        lastRow->up = newRow;
        newRow->square = squares[i];
        newRow->rowNumder = i;
    }
}

void createColumns(Column**& columns, unsigned mainSquareSize){
    columns = new Column*[static_cast<int>(pow(mainSquareSize, 2))];
    Column* firstColumn = new Column;
    *columns = firstColumn;
    Column* lastColumn = new Column;
    firstColumn->right = lastColumn;
    firstColumn->left = lastColumn;
    firstColumn->x = 0;
    firstColumn->y = 0;
    firstColumn->columnNumber = 0;
    lastColumn->left = firstColumn;
    lastColumn->right = firstColumn;
    lastColumn->x = (static_cast<int>(pow(mainSquareSize, 2)) - 1) % mainSquareSize;
    lastColumn->y = (static_cast<int>(pow(mainSquareSize, 2)) - 1) / mainSquareSize;
    lastColumn->columnNumber = static_cast<unsigned>(pow(mainSquareSize, 2)) - 1;
    for(unsigned i = 1; i < static_cast<unsigned>(pow(mainSquareSize, 2)) - 1; ++i){
        Column* newElement = new Column;
        newElement->right = lastColumn;
        newElement->left = lastColumn->left;
        newElement->x = i / mainSquareSize;
        newElement->y = i % mainSquareSize;
        newElement->columnNumber = i;
        lastColumn->left->right = newElement;
        lastColumn->left = newElement;
    }
}


void insertElement(Row*& row, Column*& column){
    Element* newElement = new Element;
    newElement->column = column;
    newElement->row = row;

    if(row->countElements){
        row->countElements++;
        row->elementsHEAD->right->left = newElement;
        newElement->right = row->elementsHEAD->right;
        row->elementsHEAD->right = newElement;
        newElement->left = row->elementsHEAD;
    }

    if(column->countElements){
        column->countElements++;
        column->elementsHEAD->up->down = newElement;
        newElement->up = column->elementsHEAD->up;
        column->elementsHEAD->up = newElement;
        newElement->down = column->elementsHEAD;
    }

    if(!row->countElements){
        row->countElements++;
        row->elementsHEAD = new Element;
        row->elementsHEAD = newElement;
        newElement->left = newElement;
        newElement->right = newElement;
    }
    if(!column->countElements){
        column->countElements++;
        column->elementsHEAD = new Element;
        column->elementsHEAD = newElement;
        newElement->up = newElement;
        newElement->down = newElement;
    }
}

void createElements(Row**& rows, Column**& colums){
    Row* currentRow = *rows;
    do{
        for(unsigned y = currentRow->square.getY(); y < currentRow->square.getSideSize() + currentRow->square.getY(); ++y){
            for(unsigned x = currentRow->square.getX(); x < currentRow->square.getSideSize() + currentRow->square.getX(); ++x){
                Column* currentColumn = *colums;
                do{
                    currentColumn = currentColumn->right;
                }while(currentColumn->x != x || currentColumn->y != y);
                insertElement(currentRow, currentColumn);
            }
        }
        currentRow = currentRow->up;
    }while(currentRow != *rows);
}

void deleteRow(Row**& rows, Row*& row2delete){
    row2delete->DELETED = true;
    Row* currentRow = *rows;
    while(currentRow != row2delete)
        currentRow = currentRow->down;

    currentRow->up->down = currentRow->down;
    currentRow->down->up = currentRow->up;
    if(currentRow == *rows)
        *rows = currentRow->down;
}

void deleteColumn(Column** columns, Column*& column2delete){
    column2delete->DELETED = true;
    Column* currentColumn = *columns;
    while(currentColumn != column2delete)
        currentColumn = currentColumn->right;

    currentColumn->left->right = currentColumn->right;
    currentColumn->right->left = currentColumn->left;
    if(currentColumn == *columns)
        *columns = currentColumn->right;
}

void insert2Column(Column** columns, std::vector<class Column*>& deletedColumn){
    Column* currentColumn;
    for(unsigned i = 0; i < deletedColumn.size(); ++i){
        currentColumn = *columns;
        if(deletedColumn[i]->columnNumber < currentColumn->columnNumber)
            *columns = deletedColumn[i];
        if(deletedColumn[i]->columnNumber < currentColumn->columnNumber ||
           deletedColumn[i]->columnNumber > currentColumn->left->columnNumber);
        else
            while(currentColumn->columnNumber < deletedColumn[i]->columnNumber)
                currentColumn = currentColumn->right;
        deletedColumn[i]->right = currentColumn;
        deletedColumn[i]->left = currentColumn->left;
        currentColumn->left->right = deletedColumn[i];
        currentColumn->left = deletedColumn[i];
        deletedColumn[i]->DELETED = false;
    }
    for(unsigned i = 0 ; i < deletedColumn.size(); ++i)
        deletedColumn.pop_back();
}

void insert2Row(Row**& rows, std::vector <class Row*>& deletedRow){
    Row* currentRow;
    for(unsigned i = 0; i < deletedRow.size(); ++i){
        currentRow = *rows;
        if(deletedRow[i]->rowNumder < currentRow->rowNumder)
            *rows = deletedRow[i];
        if(deletedRow[i]->rowNumder < currentRow->rowNumder ||
           deletedRow[i]->rowNumder > currentRow->up->rowNumder);
        else
            while(currentRow->rowNumder < deletedRow[i]->rowNumder)
                currentRow = currentRow->down;
        deletedRow[i]->down = currentRow;
        deletedRow[i]->up = currentRow->up;
        currentRow->up->down = deletedRow[i];
        currentRow->up = deletedRow[i];
        deletedRow[i]->DELETED = false;
    }
    for(unsigned i = 0 ; i < deletedRow.size(); ++i)
        deletedRow.pop_back();
}

unsigned getSize(Element* elementHEAD){
    Element* currentElement = elementHEAD;
    unsigned count = 0;
    do{
        currentElement = currentElement->down;
       if(!currentElement->row->DELETED)
            ++count;
    }while(currentElement != elementHEAD);
    return count;
};

Column* chooseMinColumn(Column** column, unsigned& maxCount){ // проблема здесь
    maxCount = 0;
    Column* currentColumn = *column;
    Column* minColumn = *column;
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
    }while(currentColumn != *column);
    return minColumn;
}

void algorithmX(Column**, Row**, Row*, std::vector <int>&,
                std::vector <std::vector <int>>&);

void algorithmXChooseRows(Column** columns, Row** rows, std::vector<int>& currentSolution,
                          std::vector <std::vector <int>>& SOLUTIONS){
    unsigned maxCount = 0;
    Column* minColumn = chooseMinColumn(columns, maxCount);
    Element* currentColumnElement = minColumn->elementsHEAD;
    std::cout << "MAX " << maxCount << std::endl;
    std::cout << "MIN COLUMN " << minColumn->countElements << " " << minColumn->x << minColumn->y << std::endl;
    if(maxCount == 1){
        std::cout << "END";
        Row* curRow = *rows;
        do{
            currentSolution.push_back(curRow->rowNumder);
            curRow = curRow->down;
        }while(curRow != *rows);
        SOLUTIONS.push_back(currentSolution);
        for(int i = 0; i < currentSolution.size(); ++i){
            currentSolution.pop_back();
        }
        return;
    }

    if(maxCount == 0){
        for(unsigned i = 0; i < SOLUTIONS.size(); ++i){
            std::cout << std::endl;
            for(unsigned j = 0; j < SOLUTIONS[i].size(); ++j){
                std::cout << " " << SOLUTIONS[i][j];
            }
        }
        std::cout << "GOVNO";
        exit(0);
    }

    do{
        std::cout << "WANTED TO MAIN ROW" << currentColumnElement->row->square.getX()
                                << currentColumnElement->row->square.getY()
                                << currentColumnElement->row->square.getSideSize() << std::endl;
        if(currentColumnElement->row->DELETED){
            currentColumnElement = currentColumnElement->down;
            continue;
        }
        std::cout << "MAIN ROW" << currentColumnElement->row->square.getX()
                                << currentColumnElement->row->square.getY()
                                << currentColumnElement->row->square.getSideSize() << std::endl;
        algorithmX(columns, rows, currentColumnElement->row, currentSolution,
                   SOLUTIONS);
        currentColumnElement = currentColumnElement->down;
    }while(currentColumnElement != minColumn->elementsHEAD);
}

void algorithmX(Column** columns, Row** rows, Row* row2DELETE, std::vector <int>& currentSolution,
                std::vector <std::vector <int>>& SOLUTIONS){
    std::cout << "МАТРИЦА ДЛЯ ФУНКЦИИ " << std::endl;
    printRows(rows);
    std::vector <class Row*> deletedRows;
    std::vector <class Column*> deletedColumns;
    Element* currentColumn = row2DELETE->elementsHEAD;
    do{
        if(currentColumn->column->DELETED)
            continue;
        Element* currentRow = currentColumn->column->elementsHEAD;
        do{
            if(currentRow->row == row2DELETE || currentRow->row->DELETED){
                currentRow = currentRow->down;
                continue;
            }
            std::cout << "DELETE ROW " << currentRow->row->square.getX()
                                << currentRow->row->square.getY()
                                << currentRow->row->square.getSideSize() << std::endl;
            deletedRows.push_back(currentRow->row);
            deleteRow(rows, currentRow->row);
            currentRow = currentRow->down;
        }while(currentRow != currentColumn->column->elementsHEAD);
        std::cout << "DELETE COLUMN " << currentColumn->column->x << currentColumn->column->y << std::endl;
        deletedColumns.push_back(currentColumn->column);
        deleteColumn(columns, currentColumn->column);
        currentColumn = currentColumn->right;
    }while(currentColumn != row2DELETE->elementsHEAD);
    std::cout << "DELETE MAIN ROW: " << row2DELETE->square.getX()
              << row2DELETE->square.getY()
              << row2DELETE->square.getSideSize() << std::endl;
    deletedRows.push_back(row2DELETE);
    deleteRow(rows, row2DELETE);
    std::cout << "МАТРИЦА ПОСЛЕ ОТРАБОТКИ ФУНКЦИИ " << std::endl;
    printColumns(columns);
    printRows(rows);
    algorithmXChooseRows(columns, rows, currentSolution, SOLUTIONS);
    std::cout << "ВОСТАНОВИМ МАТРИЦУ" << std::endl;
    insert2Row(rows, deletedRows);
    insert2Column(columns, deletedColumns);
}

int main(){
    unsigned mainSquareSize = 0;
    std::cin >> mainSquareSize;
    std::vector <Square> squares;
    countRows(mainSquareSize, squares);
    Row** rows;
    Column** columns;
    createRows(rows, squares);
    createColumns(columns, mainSquareSize);
    createElements(rows, columns);
    std::vector <int> currentSolution;
    std::vector <std::vector <int>> SOLUTIONS;
    algorithmXChooseRows(columns, rows, currentSolution, SOLUTIONS);
    return 0;
}











