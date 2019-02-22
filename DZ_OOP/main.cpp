#include <iostream>

class Matrix{
private:
public:
    unsigned rowNum;
    unsigned columnNum;
    unsigned** matrix;
public:
    void trasposeMatrix();
    void operator *= (const class Matrix&);
    void operator += (const class Matrix&);
    friend std::istream& operator >> (std::istream&, class Matrix&);
    friend std::ostream& operator << (std::ostream&, const class Matrix&);
    ~Matrix();
};

std::istream& operator>> (std::istream& in, class Matrix& matrix){
    std::cout << "INPUT SIZE: " << std::endl;
    in >> matrix.rowNum;
    in >> matrix.columnNum;
    matrix.matrix = new unsigned*[matrix.rowNum];
    std::cout << "INPUT ELEMENTS: " << std::endl;
    for(unsigned y = 0; y < matrix.rowNum; ++y){
        matrix.matrix[y] = new unsigned[matrix.columnNum];
        std::cout << "ROW " << y << std::endl;
        for(unsigned x = 0; x < matrix.columnNum; ++x){
            in >> matrix.matrix[y][x];
        }
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, const class Matrix& matrix){
    for(unsigned y = 0; y < matrix.rowNum; ++y){
        out << std::endl;
        for(unsigned x = 0; x < matrix.columnNum; ++x){
            out << matrix.matrix[y][x] << " ";
        }
    }
    return out;
}

void Matrix::trasposeMatrix(){
    unsigned** newMatrix = new unsigned*[columnNum];
    for(unsigned i = 0; i < columnNum; ++i)
        newMatrix[i] = new unsigned[rowNum];
    for(unsigned i = 0; i < columnNum; ++i){
        for(unsigned j = 0; j < rowNum; ++j){
            newMatrix[i][j] = matrix[j][i];
        }
    }
    for(unsigned i = 0; i < rowNum; ++i)
        delete[] matrix[i];
    delete[] matrix;
    matrix = newMatrix;
    unsigned temp = rowNum;
    rowNum = columnNum;
    columnNum = temp;
}

void Matrix::operator *= (const Matrix& newMatrix){
    unsigned** resultMatrix = new unsigned*[rowNum];
    for(unsigned i = 0; i < rowNum; ++i)
        resultMatrix[i] = new unsigned[newMatrix.columnNum];
    if(rowNum != newMatrix.columnNum || columnNum != newMatrix.rowNum){
        std::cout << "IT`S imposible";
        return;
    }

    for(unsigned i = 0; i < rowNum; ++i){
        for(unsigned j = 0; j < newMatrix.columnNum; ++j){
            resultMatrix[i][j] = 0;
            for(unsigned k = 0; k < columnNum; ++k){
                resultMatrix[i][j] += matrix[i][k] * newMatrix.matrix[k][j];
            }
        }
    }

    for(unsigned i = 0; i < rowNum; ++i)
        delete[] matrix[i];
    delete[] matrix;
    matrix = resultMatrix;
}

void Matrix::operator +=(const Matrix& newMatrix){
    if(rowNum != newMatrix.rowNum || columnNum != newMatrix.columnNum){
        std::cout << "IT`S imposible";
        return;
    }
    for(unsigned y = 0; y < rowNum; ++y)
        for(unsigned x = 0; x < columnNum; ++x)
            matrix[y][x] += newMatrix.matrix[y][x];
}

Matrix::~Matrix(){
    for(unsigned i = 0; i < rowNum; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

int main(){
    Matrix matrix1;
    Matrix matrix2;
    std::cin >> matrix1;
    std::cout << "second matrix" << std::endl;
    std::cin >> matrix2;
    std::cout << matrix1;
    std::cout << matrix2;
    matrix1 *= matrix2;
    std::cout << matrix1;
    return 0;
}
