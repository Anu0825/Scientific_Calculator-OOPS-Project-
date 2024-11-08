#include <iostream>
#include <numeric>  // for std::gcd in C++17
#include <stdexcept>  // for std::invalid_argument, std::runtime_error

class Fraction {
private:
    int numerator;
    int denominator;

    // Helper function to simplify the fraction
    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        // Keep the denominator positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructor with error handling
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Error: Denominator cannot be zero.");
        }
        simplify();
    }

    // Overload + operator for addition
    Fraction operator+(const Fraction& other) const {
        try {
            int num = numerator * other.denominator + other.numerator * denominator;
            int den = denominator * other.denominator;
            return Fraction(num, den);
        } catch (const std::exception& e) {
            throw std::runtime_error("Error in addition: " + std::string(e.what()));
        }
    }

    // Overload - operator for subtraction
    Fraction operator-(const Fraction& other) const {
        try {
            int num = numerator * other.denominator - other.numerator * denominator;
            int den = denominator * other.denominator;
            return Fraction(num, den);
        } catch (const std::exception& e) {
            throw std::runtime_error("Error in subtraction: " + std::string(e.what()));
        }
    }

    // Overload * operator for multiplication
    Fraction operator*(const Fraction& other) const {
        try {
            int num = numerator * other.numerator;
            int den = denominator * other.denominator;
            return Fraction(num, den);
        } catch (const std::exception& e) {
            throw std::runtime_error("Error in multiplication: " + std::string(e.what()));
        }
    }

    // Overload / operator for division with error handling
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Error: Cannot divide by zero.");
        }
        try {
            int num = numerator * other.denominator;
            int den = denominator * other.numerator;
            return Fraction(num, den);
        } catch (const std::exception& e) {
            throw std::runtime_error("Error in division: " + std::string(e.what()));
        }
    }

    // Overload == operator to check equality
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Overload << operator for output
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
        out << fraction.numerator;
        if (fraction.denominator != 1) {
            out << "/" << fraction.denominator;
        }
        return out;
    }
};

int main() {
    try {
        Fraction f1(1, 2);  // Represents 1/2
        Fraction f2(3, 4);  // Represents 3/4

        // Perform operations
        Fraction sum = f1 + f2;
        Fraction difference = f1 - f2;
        Fraction product = f1 * f2;
        Fraction quotient = f1 / f2;

        // Display results
        std::cout << "f1 = " << f1 << "\n";
        std::cout << "f2 = " << f2 << "\n";
        std::cout << "f1 + f2 = " << sum << "\n";
        std::cout << "f1 - f2 = " << difference << "\n";
        std::cout << "f1 * f2 = " << product << "\n";
        std::cout << "f1 / f2 = " << quotient << "\n";

    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid Argument: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}
