#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Friend functions for basic operations
    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);

    // Friend functions for complex properties
    friend double magnitude(const Complex& c);
    friend double argument(const Complex& c);
    friend Complex conjugate(const Complex& c);

    // Get real part
    double realPart() const {
        return real;
    }

    // Get imaginary part
    double imaginaryPart() const {
        return imag;
    }

    // Display in rectangular form
    void displayRectangular() const {
        std::cout << real << (imag >= 0 ? " + " : " - ") << std::abs(imag) << "i" << std::endl;
    }

    // Display in polar form (magnitude and argument)
    void displayPolar() const {
        std::cout << "Magnitude: " << magnitude(*this) << ", Argument: " << argument(*this) << " radians" << std::endl;
    }
};

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

// Argument (angle in radians)
double argument(const Complex& c) {
    return std::atan2(c.imag, c.real);
}

// Conjugate
Complex conjugate(const Complex& c) {
    return Complex(c.real, -c.imag);
}

int main() {
    Complex c1(3, 4);  // 3 + 4i
    Complex c2(1, -2); // 1 - 2i

    std::cout << "Complex number c1 in rectangular form: ";
    c1.displayRectangular();
    std::cout << "Complex number c2 in rectangular form: ";
    c2.displayRectangular();

    // Addition
    Complex cAdd = c1 + c2;
    std::cout << "\nc1 + c2 = ";
    cAdd.displayRectangular();

    // Subtraction
    Complex cSub = c1 - c2;
    std::cout << "c1 - c2 = ";
    cSub.displayRectangular();

    // Multiplication
    Complex cMul = c1 * c2;
    std::cout << "c1 * c2 = ";
    cMul.displayRectangular();

    // Division
    Complex cDiv = c1 / c2;
    std::cout << "c1 / c2 = ";
    cDiv.displayRectangular();

    // Magnitude of c1
    std::cout << "\nMagnitude of c1: " << magnitude(c1) << std::endl;

    // Argument of c1
    std::cout << "Argument of c1 (radians): " << argument(c1) << std::endl;

    // Conjugate of c1
    Complex cConj = conjugate(c1);
    std::cout << "Conjugate of c1: ";
    cConj.displayRectangular();

    // Display in polar form
    std::cout << "\nc1 in polar form: ";
    c1.displayPolar();
    std::cout << "c2 in polar form: ";
    c2.displayPolar();

    return 0;
}