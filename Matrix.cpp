#include "Matrix.h"

// Constructor
Matrix::Matrix(int r, int c) : rows(r), cols(c), mat(r, std::vector<double>(c, 0)) {}

// Helper method to get cofactor
Matrix Matrix::getCofactor(int p, int q, int n) const {
    Matrix temp(n - 1, n - 1);
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp.mat[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return temp;
}

// Element setters and getters
void Matrix::setElement(int i, int j, double value) {
    if (i >= rows || j >= cols)
        throw std::out_of_range("Index out of range");
    mat[i][j] = value;
}

double Matrix::getElement(int i, int j) const {
    if (i >= rows || j >= cols)
        throw std::out_of_range("Index out of range");
    return mat[i][j];
}

// Addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimensions do not match for addition");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
    return result;
}

// Subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimensions do not match for subtraction");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
    return result;
}

// Multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++)
            for (int k = 0; k < cols; k++)
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
    return result;
}

// Other methods (transpose, determinant, adjoint, inverse, rank, etc.)...
// Implement them similarly with error handling.

void Matrix::display() const {
    for (const auto& row : mat) {
        for (double val : row) {
            std::cout << std::setw(8) << val << " ";
        }
        std::cout << std::endl;
    }
}
