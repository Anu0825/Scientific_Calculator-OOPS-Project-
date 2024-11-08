#include <iostream>
#include <cmath>
#include <map>
#include <string>

std::map<std::string, double> trigonometryFunctions(double angleRad)
{
    std::map<std::string, double> results;

    // Basic trigonometric functions
    results["sin"] = std::sin(angleRad);
    results["cos"] = std::cos(angleRad);
    results["tan"] = std::tan(angleRad);

    // Inverse trigonometric functions
    // Use try-catch in case the value is out of domain
    try
    {
        results["arcsin"] = std::asin(results["sin"]);
    }
    catch (...)
    {
        results["arcsin"] = NAN;
    }

    try
    {
        results["arccos"] = std::acos(results["cos"]);
    }
    catch (...)
    {
        results["arccos"] = NAN;
    }

    try
    {
        results["arctan"] = std::atan(results["tan"]);
    }
    catch (...)
    {
        results["arctan"] = NAN;
    }

    // Hyperbolic trigonometric functions
    results["sinh"] = std::sinh(angleRad);
    results["cosh"] = std::cosh(angleRad);
    results["tanh"] = std::tanh(angleRad);

    // Inverse hyperbolic functions
    results["arcsinh"] = std::asinh(results["sinh"]);
    results["arccosh"] = std::acosh(results["cosh"]);
    results["arctanh"] = std::atanh(results["tanh"]);

    return results;
}

std::map<std::string, double> logarithmicFunctions(double value)
{
    std::map<std::string, double> results;

    // Basic logarithmic functions
    if (value > 0)
    {
        results["ln"] = std::log(value);      // Natural logarithm (base e)
        results["log10"] = std::log10(value); // Logarithm base 10
        results["log2"] = std::log2(value);   // Logarithm base 2
    }
    else
    {
        results["ln"] = NAN;
        results["log10"] = NAN;
        results["log2"] = NAN;
    }

    // Custom base logarithm function (e.g., base 5)
    double base = 5.0;
    if (value > 0 && base > 0 && base != 1)
    {
        results["log_base_" + std::to_string(static_cast<int>(base))] = std::log(value) / std::log(base);
    }
    else
    {
        results["log_base_" + std::to_string(static_cast<int>(base))] = NAN;
    }

    return results;
}

std::map<std::string, double> exponentialFunctions(double value)
{
    std::map<std::string, double> results;

    // Standard exponential function
    results["exp"] = std::exp(value); // e^value

    // Exponential with a custom base (e.g., 2^value)
    double base = 2.0;
    results["base_" + std::to_string(static_cast<int>(base)) + "^value"] = std::pow(base, value);

    // Exponential for other bases (base 10 as an example)
    base = 10.0;
    results["base_" + std::to_string(static_cast<int>(base)) + "^value"] = std::pow(base, value);

    // Square and cube functions as specific examples
    results["square"] = std::pow(value, 2); // value^2
    results["cube"] = std::pow(value, 3);   // value^3

    return results;
}

std::map<std::string, bool> logicalOperations(bool a, bool b)
{
    std::map<std::string, bool> results;

    // Logical operators
    results["a && b"] = a && b; // Logical AND
    results["a || b"] = a || b; // Logical OR
    results["!a"] = !a;         // Logical NOT on a
    results["!b"] = !b;         // Logical NOT on b

    return results;
}

std::map<std::string, int> bitwiseOperations(int x, int y)
{
    std::map<std::string, int> results;

    // Bitwise operators
    results["x & y"] = x & y;            // Bitwise AND
    results["x | y"] = x | y;            // Bitwise OR
    results["x ^ y"] = x ^ y;            // Bitwise XOR
    results["~x (1's complement)"] = ~x; // Bitwise NOT (1's complement) on x
    results["~y (1's complement)"] = ~y; // Bitwise NOT (1's complement) on y

    // 2's Complement
    results["2's complement of x"] = ~x + 1; // 2's complement of x
    results["2's complement of y"] = ~y + 1; // 2's complement of y

    return results;
}

unsigned long long factorial(int n)
{
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

// Function to calculate GCD using Euclid's Algorithm
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate LCM using the GCD
int lcm(int a, int b)
{
    return std::abs(a * b) / gcd(a, b);
}

void calculateRootsAndPowers(double value, double exponent)
{
    std::cout << "Value: " << value << std::endl;
    std::cout << "Square Root (√" << value << "): " << std::sqrt(value) << std::endl;
    std::cout << "Cube Root (³√" << value << "): " << std::cbrt(value) << std::endl;
    std::cout << "Power (" << value << "^" << exponent << "): " << std::pow(value, exponent) << std::endl;
}

// Function to calculate nCr (Combinations)
unsigned long long nCr(int n, int r)
{
    if (r > n)
        return 0; // If r is greater than n, nCr is 0
    return factorial(n) / (factorial(r) * factorial(n - r));
}

// Function to calculate nPr (Permutations)
unsigned long long nPr(int n, int r)
{
    if (r > n)
        return 0; // If r is greater than n, nPr is 0
    return factorial(n) / factorial(n - r);
}

int main()
{
    double angleDeg = 45.0;                    // Angle in degrees
    double angleRad = angleDeg * M_PI / 180.0; // Convert to radians

    std::map<std::string, double> result = trigonometryFunctions(angleRad);

    // Output the results
    for (const auto &pair : result)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    double value = 100.0; // Value for which to calculate logarithms

    std::map<std::string, double> result = logarithmicFunctions(value);

    // Output the results
    for (const auto &pair : result)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    double value = 3.0; // The exponent to use for calculations

    std::map<std::string, double> result = exponentialFunctions(value);

    // Output the results
    for (const auto &pair : result)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}