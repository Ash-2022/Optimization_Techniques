#ifndef MATRIX_TRANSFORMATION_H
#define MATRIX_TRANSFORMATION_H

#include <algorithm>
#include <vector>

using namespace std;

class Matrix {
   private:
    vector<vector<double>> matrix;
    int rows, cols;

   public:
    Matrix(vector<vector<double>> matrix)
        : matrix(matrix), rows(matrix.size()), cols(matrix[0].size()) {}
    Matrix(int row, int col)
        : rows(row), cols(col), matrix(row, vector<double>(col)) {}
    void setRow(int row) { this->rows = row; }
    void setCol(int col) { this->cols = col; }
    void setMatrix(vector<vector<double>> matrix) { this->matrix = matrix; }
    int getRow() { return this->rows; }
    int getCol() { return this->cols; }
    vector<vector<double>> getMatrix() { return this->matrix; }
    
};

#endif
