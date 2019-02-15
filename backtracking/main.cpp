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
                  << " sizeSide " << currentRow->square.getSideSize();
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
                  << " COLUMN Y =  " << currentColumn->y;
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
    lastRow->square = squares[squares.size()-1];
    for(unsigned i = 1; i < squares.size() - 1; ++i){
        Row* newRow = new Row;
        newRow->down = lastRow;
        newRow->up = lastRow->up;
        lastRow->up->down = newRow;
        lastRow->up = newRow;
        newRow->square = squares[i];
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
    lastColumn->left = firstColumn;
    lastColumn->right = firstColumn;
    lastColumn->x = (static_cast<int>(pow(mainSquareSize, 2)) - 1) % mainSquareSize;
    lastColumn->y = (static_cast<int>(pow(mainSquareSize, 2)) - 1) / mainSquareSize;
    for(unsigned i = 1; i < static_cast<unsigned>(pow(mainSquareSize, 2)) - 1; ++i){
        Column* newElement = new Column;
        newElement->right = lastColumn;
        newElement->left = lastColumn->left;
        newElement->x = i / mainSquareSize;
        newElement->y = i % mainSquareSize;
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
    Row* currentRow = *rows;
    while(currentRow != row2delete)
        currentRow = currentRow->down;
    if(currentRow == *rows)
        *rows = currentRow->down;
    currentRow->up->down = currentRow->down;
    currentRow->down->up = currentRow->up;
    row2delete->DELETED = true;
    //delete row2delete;
}

void deleteColumn(Column**& columns, Column*& column2delete){
    Column* currentColumn = *columns;
    while(currentColumn != column2delete)
        currentColumn = currentColumn->right;
    if(currentColumn == *columns)
        *columns = currentColumn->right;
    currentColumn->left->right = currentColumn->right;
    currentColumn->right->left = currentColumn->left;
    column2delete->DELETED = true;
    //delete column2delete;
}

void insert2Column(Column**& columns, std::vector<class Column*> deletedColumn){
    Column* lastColumn = *columns;
    lastColumn = lastColumn->left;
    for(unsigned i = 0; i < deletedColumn.size(); ++i){
        deletedColumn[i]->right = lastColumn;
        deletedColumn[i]->left = lastColumn->left;
        lastColumn->left->right = deletedColumn[i];
        lastColumn->left = deletedColumn[i];
        deletedColumn[i]->DELETED = false;
    }
    for(unsigned i = 0 ; i < deletedColumn.size(); ++i)
        deletedColumn.pop_back();
}

void insert2Row(Row**& rows, std::vector <class Row*> deletedRow){
    Row* lastRow = *rows;
    lastRow = lastRow->up;
    for(unsigned i = 0; i < deletedRow.size(); ++i){
        deletedRow[i]->down = lastRow;
        deletedRow[i]->up = lastRow->up;
        lastRow->up->down = deletedRow[i];
        lastRow->up = deletedRow[i];
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

Column* insertMinColumn(Column** column, unsigned& maxCount){
    maxCount = 0;
    Column* currentColumn = *column;
    Column* minColumn = *column;
    do{
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

void algorithmX(Row** rows, Column** column){;
    unsigned maxColumnSize = 0;
    std::vector <class Row*> deletedRows;
    std::vector <class Column*> deletedColums;
    Column* minColumn = insertMinColumn(column, maxColumnSize);
    std::cout << "MIN COUNT " << minColumn->countElements << std::endl;
    std::cout << "MAX COUNT " << maxColumnSize << std::endl;
    if(maxColumnSize == 1){
        return;
    }
    Element* currentColumnElement = minColumn->elementsHEAD;
    do{
        Element* currentRowElement = currentColumnElement->row->elementsHEAD;
        do{
            Element* columnDELETE = currentRowElement->column->elementsHEAD;
            do{
                if(columnDELETE->row != currentColumnElement->row && !columnDELETE->row->DELETED){
                    std::cout << "DELETE ROW: " << columnDELETE->row->square.getX()
                              << columnDELETE->row->square.getY()
                              << columnDELETE->row->square.getSideSize() << std::endl;
                    deletedRows.push_back(columnDELETE->row);
                    deleteRow(rows, columnDELETE->row);
                }
                columnDELETE = columnDELETE->down;
            }while(columnDELETE != currentRowElement->column->elementsHEAD);
            deletedColums.push_back(currentRowElement->column);
            deleteColumn(column, currentRowElement->column);
            currentRowElement = currentRowElement->right;
        }while(currentRowElement != currentColumnElement->row->elementsHEAD);
        std::cout << "DELETE ROW AAAA: " << currentColumnElement->row->square.getX()
                  << currentColumnElement->row->square.getY()
                  << currentColumnElement->row->square.getSideSize() << std::endl;
        deletedRows.push_back(currentColumnElement->row);
        deleteRow(rows, currentColumnElement->row);
        std::cout << "РЕЗУЛЬТАТЫ ПОСЛЕ ФУНКЦИИ" << std::endl;
        printColumns(column);
        printRows(rows);
        algorithmX(rows, column);
        std::cout << "ПОСЛЕ ОТРАБОТКИ РЕКУРСИИ" << std::endl;
        printColumns(column);
        printRows(rows);

        std::cout << "ВОСТАНОВЛЕННАЯ МАТРИЦА" << std::endl;
        insert2Column(column, deletedColums);
        insert2Row(rows, deletedRows);
        printColumns(column);
        printRows(rows);
        currentColumnElement = currentColumnElement->down;
    }while(currentColumnElement != minColumn->elementsHEAD);
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
    algorithmX(rows, columns);
    return 0;
}




















