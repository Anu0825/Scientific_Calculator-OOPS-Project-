#include "VectorOperations.h"
#include <iostream>
#include <cmath>

using namespace std;

// Constructor for initializing the vector with given components
Vector::Vector(const vector<double>& components) : components(components) {}

// Display the vector
void Vector::display() const {
    cout << "(";
    for (size_t i = 0; i < components.size(); i++) {
        cout << components[i];
        if (i < components.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}

// Overloading + operator for vector addition
VectorOperations* Vector::operator+(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    if (components.size() != v.components.size()) {
        throw invalid_argument("Vectors must have the same dimension for addition");
    }

    vector<double> result(components.size());
    for (size_t i = 0; i < components.size(); i++) {
        result[i] = components[i] + v.components[i];
    }
    return new Vector(result);
}

// Overloading - operator for vector subtraction
VectorOperations* Vector::operator-(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    if (components.size() != v.components.size()) {
        throw invalid_argument("Vectors must have the same dimension for subtraction");
    }

    vector<double> result(components.size());
    for (size_t i = 0; i < components.size(); i++) {
        result[i] = components[i] - v.components[i];
    }
    return new Vector(result);
}

// Dot product of two vectors
double Vector::dot(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    if (components.size() != v.components.size()) {
        throw invalid_argument("Vectors must have the same dimension for dot product");
    }

    double result = 0;
    for (size_t i = 0; i < components.size(); i++) {
        result += components[i] * v.components[i];
    }
    return result;
}

// Cross product of two 3D vectors
VectorOperations* Vector::cross(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    if (components.size() != 3 || v.components.size() != 3) {
        throw invalid_argument("Cross product is only defined for 3D vectors");
    }

    vector<double> result(3);
    result[0] = components[1] * v.components[2] - components[2] * v.components[1];
    result[1] = components[2] * v.components[0] - components[0] * v.components[2];
    result[2] = components[0] * v.components[1] - components[1] * v.components[0];

    return new Vector(result);
}

// Magnitude of the vector
double Vector::magnitude() const {
    double sum = 0;
    for (double comp : components) {
        sum += comp * comp;
    }
    return sqrt(sum);
}

// Normalize the vector (convert to unit vector)
VectorOperations* Vector::normalize() const {
    double mag = magnitude();
    if (mag == 0) {
        throw invalid_argument("Cannot normalize a zero vector");
    }

    vector<double> result(components.size());
    for (size_t i = 0; i < components.size(); i++) {
        result[i] = components[i] / mag;
    }
    return new Vector(result);
}

// Angle between two vectors in radians
double Vector::angle(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    if (components.size() != v.components.size()) {
        throw invalid_argument("Vectors must have the same dimension to calculate angle");
    }

    double dotProduct = dot(v);
    double mag1 = magnitude();
    double mag2 = v.magnitude();

    if (mag1 == 0 || mag2 == 0) {
        throw invalid_argument("Cannot calculate the angle with a zero vector");
    }

    return acos(dotProduct / (mag1 * mag2));
}

// Project this vector onto another vector
VectorOperations* Vector::projectOnto(const VectorOperations& other) const {
    const Vector& v = dynamic_cast<const Vector&>(other);
    double magOther = v.magnitude();
    if (magOther == 0) {
        throw invalid_argument("Cannot project onto a zero vector");
    }

    double scale = dot(v) / (magOther * magOther);
    vector<double> result(v.components.size());
    for (size_t i = 0; i < v.components.size(); i++) {
        result[i] = v.components[i] * scale;
    }
    return new Vector(result);
}
