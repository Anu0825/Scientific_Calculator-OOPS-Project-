#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace std;

// Abstract base class for vector operations
class VectorOperations {
public:
    virtual void display() const = 0;
    virtual VectorOperations* operator+(const VectorOperations& other) const = 0;
    virtual VectorOperations* operator-(const VectorOperations& other) const = 0;
    virtual double dot(const VectorOperations& other) const = 0;
    virtual VectorOperations* cross(const VectorOperations& other) const = 0;
    virtual double magnitude() const = 0;
    virtual VectorOperations* normalize() const = 0;
    virtual double angle(const VectorOperations& other) const = 0;
    virtual VectorOperations* projectOnto(const VectorOperations& other) const = 0;
    virtual ~VectorOperations() = default;
};

class Vector : public VectorOperations {
private:
    vector<double> components;

public:
    Vector(const vector<double>& components);

    void display() const override;

    VectorOperations* operator+(const VectorOperations& other) const override;

    VectorOperations* operator-(const VectorOperations& other) const override;

    double dot(const VectorOperations& other) const override;

    VectorOperations* cross(const VectorOperations& other) const override;

    double magnitude() const override;

    VectorOperations* normalize() const override;

    double angle(const VectorOperations& other) const override;

    VectorOperations* projectOnto(const VectorOperations& other) const override;
};

#endif // VECTOR_OPERATIONS_H
