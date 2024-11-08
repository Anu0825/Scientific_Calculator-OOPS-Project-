#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>
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
    Vector(const vector<double>& components) : components(components) {}

    void display() const override {
        cout << "(";
        for (size_t i = 0; i < components.size(); i++) {
            cout << components[i];
            if (i < components.size() - 1) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
    }

    VectorOperations* operator+(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        if (components.size() != v.components.size())
            throw invalid_argument("Vectors must have the same dimension for addition");

        vector<double> result(components.size());
        for (size_t i = 0; i < components.size(); i++) {
            result[i] = components[i] + v.components[i];
        }
        return new Vector(result);
    }

    VectorOperations* operator-(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        if (components.size() != v.components.size())
            throw invalid_argument("Vectors must have the same dimension for subtraction");

        vector<double> result(components.size());
        for (size_t i = 0; i < components.size(); i++) {
            result[i] = components[i] - v.components[i];
        }
        return new Vector(result);
    }

    double dot(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        if (components.size() != v.components.size())
            throw invalid_argument("Vectors must have the same dimension for dot product");

        double result = 0;
        for (size_t i = 0; i < components.size(); i++) {
            result += components[i] * v.components[i];
        }
        return result;
    }

    VectorOperations* cross(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        if (components.size() != 3 || v.components.size() != 3)
            throw invalid_argument("Cross product is only defined for 3D vectors");

        vector<double> result(3);
        result[0] = components[1] * v.components[2] - components[2] * v.components[1];
        result[1] = components[2] * v.components[0] - components[0] * v.components[2];
        result[2] = components[0] * v.components[1] - components[1] * v.components[0];
        
        return new Vector(result);
    }

    double magnitude() const override {
        double sum = 0;
        for (double comp : components) {
            sum += comp * comp;
        }
        return sqrt(sum);
    }

    VectorOperations* normalize() const override {
        double mag = magnitude();
        if (mag == 0)
            throw invalid_argument("Cannot normalize a zero vector");

        vector<double> result(components.size());
        for (size_t i = 0; i < components.size(); i++) {
            result[i] = components[i] / mag;
        }
        return new Vector(result);
    }

    double angle(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        if (components.size() != v.components.size())
            throw invalid_argument("Vectors must have the same dimension to calculate angle");

        double dotProduct = dot(v);
        double mag1 = magnitude();
        double mag2 = v.magnitude();

        if (mag1 == 0 || mag2 == 0)
            throw invalid_argument("Cannot calculate the angle with a zero vector");

        return acos(dotProduct / (mag1 * mag2));
    }

    VectorOperations* projectOnto(const VectorOperations& other) const override {
        const Vector& v = dynamic_cast<const Vector&>(other);
        double magOther = v.magnitude();
        if (magOther == 0)
            throw invalid_argument("Cannot project onto a zero vector");

        double scale = dot(v) / (magOther * magOther);
        vector<double> result(v.components.size());
        for (size_t i = 0; i < v.components.size(); i++) {
            result[i] = v.components[i] * scale;
        }
        return new Vector(result);
    }
};

int main() {
    Vector v1({3, 4, 5});
    Vector v2({1, 0, -1});

    cout << "Vector v1: ";
    v1.display();
    cout << "Vector v2: ";
    v2.display();

    // Addition
    VectorOperations* vAdd = v1 + v2;
    cout << "v1 + v2 = ";
    vAdd->display();
    delete vAdd;

    // Subtraction
    VectorOperations* vSub = v1 - v2;
    cout << "v1 - v2 = ";
    vSub->display();
    delete vSub;

    // Dot Product
    double vDot = v1.dot(v2);
    cout << "v1 . v2 = " << vDot << endl;

    // Cross Product
    VectorOperations* vCross = v1.cross(v2);
    cout << "v1 x v2 = ";
    vCross->display();
    delete vCross;

    // Angle between v1 and v2
    double vAngle = v1.angle(v2);
    cout << "Angle between v1 and v2 (in radians) = " << vAngle << endl;

    // Projection of v1 onto v2
    VectorOperations* vProj = v1.projectOnto(v2);
    cout << "Projection of v1 onto v2 = ";
    vProj->display();
    delete vProj;

    // Normalization of v1
    VectorOperations* vNorm = v1.normalize();
    cout << "Normalized v1 = ";
    vNorm->display();
    delete vNorm;

    return 0;
}