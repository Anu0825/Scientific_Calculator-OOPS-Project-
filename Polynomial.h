#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <stdexcept> // For exception handling

class Polynomial {
private:
    int degree;
    std::vector<double> coeffs;

public:
    // Constructor for a polynomial of given degree
    Polynomial(int degree, const std::vector<double>& coefficients);

    // Overloading + operator
    Polynomial operator+(const Polynomial& other) const;

    // Overloading - operator
    Polynomial operator-(const Polynomial& other) const;

    // Overloading * operator
    Polynomial operator*(const Polynomial& other) const;

    // Overloading / operator
    Polynomial operator/(double scalar) const;

    // Function to find roots for 2nd degree polynomial
    void findRoots() const;

    // Function to find roots for 3rd degree polynomial (approximate solution)
    void findRoots(double guess) const;

    // Display polynomial
    void display() const;
};

#endif // POLYNOMIAL_H
