#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <numeric>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    // Helper function to simplify the fraction
    void simplify();

public:
    // Constructor
    Fraction(int num = 0, int den = 1);

    // Overload operators
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    bool operator==(const Fraction& other) const;

    // Friend function for output
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
};

#endif // FRACTION_H
