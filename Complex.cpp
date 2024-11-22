#include "Complex.h"

// Constructor
Complex::Complex(double r, double i) : real(r), imag(i) {}

// Addition
Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

// Subtraction
Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1.real - c2.real, c1.imag - c2.imag);
}

// Multiplication
Complex operator*(const Complex& c1, const Complex& c2) {
    double realPart = c1.real * c2.real - c1.imag * c2.imag;
    double imagPart = c1.real * c2.imag + c1.imag * c2.real;
    return Complex(realPart, imagPart);
}

// Division
Complex operator/(const Complex& c1, const Complex& c2) {
    double denominator = c2.real * c2.real + c2.imag * c2.imag;
    if (denominator == 0) throw std::invalid_argument("Division by zero");
    
    double realPart = (c1.real * c2.real + c1.imag * c2.imag) / denominator;
    double imagPart = (c1.imag * c2.real - c1.real * c2.imag) / denominator;
    return Complex(realPart, imagPart);
}

// Magnitude
double magnitude(const Complex& c) {
    return std::sqrt(c.real * c.real + c.imag * c.imag);
}

// Argument
double argument(const Complex& c) {
    return std::atan2(c.imag, c.real);
}

// Conjugate
Complex conjugate(const Complex& c) {
    return Complex(c.real, -c.imag);
}

// Getters
double Complex::realPart() const {
    return real;
}

double Complex::imaginaryPart() const {
    return imag;
}

// Display in rectangular form
void Complex::displayRectangular() const {
    std::cout << real << (imag >= 0 ? " + " : " - ") << std::abs(imag) << "i" << std::endl;
}

// Display in polar form
void Complex::displayPolar() const {
    std::cout << "Magnitude: " << magnitude(*this) << ", Argument: " << argument(*this) << " radians" << std::endl;
}
