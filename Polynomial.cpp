#include "Polynomial.h"
#include <iomanip>

Polynomial::Polynomial(int degree, const std::vector<double>& coefficients) : degree(degree), coeffs(coefficients) {
    if (degree < 2 || degree > 3) {
        throw std::invalid_argument("Only 2nd and 3rd degree polynomials are supported.");
    }
    if (coeffs.size() != degree + 1) {
        throw std::invalid_argument("Coefficient size must match polynomial degree + 1.");
    }
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    if (degree != other.degree) {
        throw std::invalid_argument("Polynomials must have the same degree for addition.");
    }
    std::vector<double> result_coeffs(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        result_coeffs[i] = coeffs[i] + other.coeffs[i];
    }
    return Polynomial(degree, result_coeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    if (degree != other.degree) {
        throw std::invalid_argument("Polynomials must have the same degree for subtraction.");
    }
    std::vector<double> result_coeffs(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        result_coeffs[i] = coeffs[i] - other.coeffs[i];
    }
    return Polynomial(degree, result_coeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    int new_degree = degree + other.degree;
    std::vector<double> result_coeffs(new_degree + 1, 0);
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= other.degree; ++j) {
            result_coeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    std::vector<double> result_coeffs(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        result_coeffs[i] = coeffs[i] / scalar;
    }
    return Polynomial(degree, result_coeffs);
}

void Polynomial::findRoots() const {
    if (degree == 2) {
        double a = coeffs[0], b = coeffs[1], c = coeffs[2];
        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
            double root2 = (-b - std::sqrt(discriminant)) / (2 * a);
            std::cout << "Roots: " << root1 << ", " << root2 << "\n";
        } else {
            std::complex<double> root1 = (-b + std::sqrt(std::complex<double>(discriminant))) / (2.0 * a);
            std::complex<double> root2 = (-b - std::sqrt(std::complex<double>(discriminant))) / (2.0 * a);
            std::cout << "Complex Roots: " << root1 << ", " << root2 << "\n";
        }
    } else {
        std::cout << "Root-finding for cubic polynomials is not implemented.\n";
    }
}

void Polynomial::findRoots(double guess) const {
    if (degree == 3) {
        std::cout << "Finding roots for 3rd degree polynomial (approximate): " << std::endl;
        // Placeholder for actual cubic root calculation (advanced techniques required)
    } else {
        std::cout << "Root-finding for cubic polynomials is not implemented.\n";
    }
}

void Polynomial::display() const {
    for (int i = 0; i <= degree; ++i) {
        if (coeffs[i] == 0) continue;
        if (i > 0 && coeffs[i] > 0) std::cout << " + ";
        if (i > 0 && coeffs[i] < 0) std::cout << " - ";
        std::cout << std::abs(coeffs[i]);
        if (degree - i > 0) std::cout << "x^" << degree - i;
    }
    std::cout << "\n";
}
