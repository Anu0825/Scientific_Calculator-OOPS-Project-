#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

class Matrix {
private:
    std::vector<std::vector<double>> mat;
    int rows, cols;

    // Helper method for determinant and adjoint calculation
    Matrix getCofactor(int p, int q, int n) const;

public:
    // Constructor
    Matrix(int r, int c);

    // Element setters and getters
    void setElement(int i, int j, double value);
    double getElement(int i, int j) const;

    // Matrix operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix transpose() const;
    double determinant() const;
    Matrix adjoint() const;
    Matrix inverse() const;

    // Row echelon form and rank
    Matrix rowEchelon() const;
    int rank() const;

    // Display matrix
    void display() const;

    // Trace and eigenvalue methods (for 2x2 matrices)
    double trace() const;
    void characteristicPolynomial() const;
    std::vector<double> eigenvalues() const;
    std::vector<std::vector<double>> eigenvectors() const;
};

#endif // MATRIX_H
