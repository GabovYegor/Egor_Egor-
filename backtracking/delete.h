void algorithmX(Row** rows, Column** column){;
    unsigned maxColumnSize = 0;
    std::vector <class Row*> deletedRows;
    std::vector <class Column*> deletedColumns;
    Column* minColumn = findMinColumn(column, maxColumnSize);
    std::cout << "MIN COUNT " << minColumn->countElements << std::endl;
    std::cout << "MAX COUNT " << maxColumnSize << std::endl;
    if(maxColumnSize == 1){
        return;
    }
    Element* currentColumnElement = minColumn->elementsHEAD;
    do{
        Element* currentRowElement = currentColumnElement->row->elementsHEAD;
        std::cout << "HELLO" << currentRowElement->row->square.getX()
                  << currentRowElement->row->square.getY()
                  << currentRowElement->row->square.getSideSize() << std::endl;
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
            deletedColumns.push_back(currentRowElement->column);
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
        insert2Column(column, deletedColumns);
        insert2Row(rows, deletedRows);
        printColumns(column);
        printRows(rows);
        currentColumnElement = currentColumnElement->down;
        //break;
    }while(currentColumnElement != minColumn->elementsHEAD);
}
