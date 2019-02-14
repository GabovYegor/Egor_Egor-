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

typedef class Point{
private:
    unsigned x;
    unsigned y;
public:
    void setX(const unsigned x){this->x = x;}
    void setY(const unsigned y){this->y = y;}
    unsigned getX(){return x;}
    unsigned getY(){return y;}
    Point(){}
    Point(const int x, const int y){
        this->x = x;
        this->y = y;
    }
    bool operator ==(const class Point& Point2){
        return Point2.x == x && Point2.y == y;
    }
}Point;

typedef class Row{
public:
    Row(){num = 0;}
    Square square;
    class Row* up;
    class Row* down;
    class Element* elementsHEAD;
    unsigned num;
}Row;

typedef class Column{
public:
    Column(){num = 0;}
    class Column* left;
    class Column* right;
    unsigned num;
    Element* elementsHEAD;
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

unsigned countRows(const unsigned mainSquareSize){
    unsigned countRows = 0;
    for(unsigned iteratorSize = mainSquareSize - 1; iteratorSize > 0; --iteratorSize){ // плохо
        for(unsigned x = 0; x < mainSquareSize; ++x){
            for(unsigned y = 0; y < mainSquareSize; ++y){
                if(x + iteratorSize <= mainSquareSize && y + iteratorSize <= mainSquareSize){
                    ++countRows;
                }
            }
        }
    }
    return countRows;
}

void printRows(Row** rows){
    Row* currentRow = rows[0];
    do{
        std::cout << " X = " << currentRow->square.getX()
                  << " Y = " << currentRow->square.getY()
                  << " sizeSide " << currentRow->square.getSideSize() << std::endl;
        currentRow = currentRow->up;
    }while(currentRow != rows[0]);
}

void createRows(const unsigned mainSquareSize, Row**& rows, unsigned rowsSize){
    rows = new Row*[rowsSize];
    for(unsigned i = 0; i < rowsSize; ++i)
        rows[i] = new Row[rowsSize];
    unsigned currentRow = 0;
    for(unsigned iteratorSize = mainSquareSize - 1; iteratorSize > 0; --iteratorSize){
        for(unsigned x = 0; x < mainSquareSize; ++x){
            for(unsigned y = 0; y < mainSquareSize; ++y){
                if(x + iteratorSize <= mainSquareSize && y + iteratorSize <= mainSquareSize){
                    rows[currentRow]->num = currentRow;
                    rows[currentRow++]->square = Square(x, y, iteratorSize);
                }
            }
        }
    }
    for(unsigned i = 0; i < currentRow; ++i){
        rows[i]->up = rows[i+1];
    }
    for(unsigned i = currentRow - 1; i > 0; --i)
        rows[i]->down = rows[i-1];
    rows[0]->down = rows[currentRow - 1];
    rows[currentRow - 1]->up = rows[0];
}

void createColumns(unsigned mainSquareSize, Column**& columns){
    columns = new Column*[static_cast<int>(pow(mainSquareSize, 2))];
    for(unsigned i = 0; i < static_cast<unsigned>(pow(mainSquareSize, 2)); ++i){
        columns[i] = new Column[static_cast<int>(pow(mainSquareSize, 2))];
        columns[i]->num = i;
    }
    for(unsigned i = 0; i < pow(mainSquareSize, 2); ++i){
        columns[i]->right = columns[i+1];
    }
    for(unsigned i = pow(mainSquareSize, 2) - 1; i > 0; --i){
        columns[i]->left = columns[i+1];
    }
    columns[0]->left = columns[static_cast<int>(pow(mainSquareSize, 2)) - 1];
}


void insertElement(Row*& row, Column*& column){
    Element* newElement = new Element;
    newElement->column = column;
    newElement->row = row;
    std::cout << " NEW   " << " X = " << row->square.getX()
              << " Y = " << row->square.getY()
              << " sizeSide = " << row->square.getSideSize() << std::endl;
    if(row->num){
        row->num++;
        row->elementsHEAD->right->left = newElement;
        newElement->right = row->elementsHEAD->right;
        row->elementsHEAD->right = newElement;
        newElement->left = row->elementsHEAD;
    }

    if(column->num){
        column->num++;
        column->elementsHEAD->up->down = newElement;
        newElement->up = column->elementsHEAD->up;
        column->elementsHEAD->up = newElement;
        newElement->down = column->elementsHEAD;
    }

    if(!row->num){
        row->num++;
        row->elementsHEAD = new Element;
        row->elementsHEAD = newElement;
        newElement->left = newElement;
        newElement->right = newElement;
    }
    if(!column->num){
        column->num++;
        column->elementsHEAD = new Element;
        column->elementsHEAD = newElement;
        newElement->up = newElement;
        newElement->down = newElement;
    }
}

void createElements(Row**& rows, Column**& colums, unsigned mainSquareSize){
    Row* currentRow = rows[0];
    do{
        for(unsigned y = currentRow->square.getY(); y < currentRow->square.getSideSize(); ++y){
            for(unsigned x = currentRow->square.getX(); x < currentRow->square.getSideSize(); ++x){
                insertElement(currentRow, colums[y * mainSquareSize + x]);
            }
        }
        currentRow = currentRow->up;
    }while(currentRow != rows[0]);
}

int main(){
    unsigned mainSquareSize = 0;
    std::cin >> mainSquareSize;
    int rowsSize = countRows(mainSquareSize);
    Row** rows;
    Column** columns;
    createRows(mainSquareSize, rows, rowsSize); // создали все возможные фигуры
    printRows(rows);
    createColumns(mainSquareSize, columns);
    createElements(rows, columns, mainSquareSize);
    return 0;
}




















