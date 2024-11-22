#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0, double i = 0);

    // Friend functions for basic operations
    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);

    // Friend functions for complex properties
    friend double magnitude(const Complex& c);
    friend double argument(const Complex& c);
    friend Complex conjugate(const Complex& c);

    // Getters
    double realPart() const;
    double imaginaryPart() const;

    // Display in rectangular form
    void displayRectangular() const;

    // Display in polar form (magnitude and argument)
    void displayPolar() const;
};

#endif // COMPLEX_H
