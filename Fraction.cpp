#include "Fraction.h"

// Constructor
Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (den == 0) {
        throw std::invalid_argument("Error: Denominator cannot be zero.");
    }
    simplify();
}

// Helper function to simplify the fraction
void Fraction::simplify() {
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Addition
Fraction Fraction::operator+(const Fraction& other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

// Subtraction
Fraction Fraction::operator-(const Fraction& other) const {
    int num = numerator * other.denominator - other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

// Multiplication
Fraction Fraction::operator*(const Fraction& other) const {
    int num = numerator * other.numerator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

// Division
Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw std::invalid_argument("Error: Cannot divide by zero.");
    }
    int num = numerator * other.denominator;
    int den = denominator * other.numerator;
    return Fraction(num, den);
}

// Equality check
bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

// Output operator
std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
    out << fraction.numerator;
    if (fraction.denominator != 1) {
        out << "/" << fraction.denominator;
    }
    return out;
}
