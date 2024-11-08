#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>
using namespace std;
class Matrix {
private:
    vector<vector<double>> mat;
    int rows, cols;

    Matrix getCofactor(int p, int q, int n) const {
        Matrix temp(n - 1, n - 1);
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp.mat[i][j++] = mat[row][col];
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return temp;
    }

public:
    Matrix(int r, int c) : rows(r), cols(c), mat(r, vector<double>(c, 0)) {}

    void setElement(int i, int j, double value) {
        if (i >= rows || j >= cols)
            throw out_of_range("Index out of range");
        mat[i][j] = value;
    }

    double getElement(int i, int j) const {
        if (i >= rows || j >= cols)
            throw out_of_range("Index out of range");
        return mat[i][j];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrix dimensions do not match for addition");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[i][j] = mat[i][j] + other.mat[i][j];
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrix dimensions do not match for subtraction");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[i][j] = mat[i][j] - other.mat[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw invalid_argument("Matrix dimensions do not match for multiplication");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[j][i] = mat[i][j];
        return result;
    }

    double determinant() const {
        if (rows != cols)
            throw invalid_argument("Determinant is only defined for square matrices");

        if (rows == 1)
            return mat[0][0];

        if (rows == 2)
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

        double det = 0;
        for (int i = 0; i < cols; i++) {
            Matrix cofactor = getCofactor(0, i, rows);
            det += (i % 2 == 0 ? 1 : -1) * mat[0][i] * cofactor.determinant();
        }
        return det;
    }

    Matrix adjoint() const {
        if (rows != cols)
            throw invalid_argument("Adjoint is only defined for square matrices");

        Matrix adj(rows, cols);
        if (rows == 1) {
            adj.mat[0][0] = 1;
            return adj;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Matrix cofactor = getCofactor(i, j, rows);
                adj.mat[j][i] = (i + j) % 2 == 0 ? cofactor.determinant() : -cofactor.determinant();
            }
        }
        return adj;
    }

    Matrix inverse() const {
        double det = determinant();
        if (det == 0)
            throw invalid_argument("Singular matrix, can't find its inverse");

        Matrix adj = adjoint();
        Matrix inv(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                inv.mat[i][j] = adj.mat[i][j] / det;

        return inv;
    }

    Matrix rowEchelon() const {
        Matrix result = *this;
        int lead = 0;
        for (int r = 0; r < rows; r++) {
            if (lead >= cols)
                return result;
            int i = r;
            while (result.mat[i][lead] == 0) {
                i++;
                if (i == rows) {
                    i = r;
                    lead++;
                    if (lead == cols)
                        return result;
                }
            }
            swap(result.mat[i], result.mat[r]);
            double lv = result.mat[r][lead];
            for (int j = 0; j < cols; j++) {
                result.mat[r][j] /= lv;
            }
            for (int i = 0; i < rows; i++) {
                if (i != r) {
                    lv = result.mat[i][lead];
                    for (int j = 0; j < cols; j++) {
                        result.mat[i][j] -= lv * result.mat[r][j];
                    }
                }
            }
            lead++;
        }
        return result;
    }

    int rank() const {
        Matrix ref = rowEchelon();
        int rank = 0;
        for (int i = 0; i < rows; i++) {
            bool allZero = true;
            for (int j = 0; j < cols; j++) {
                if (abs(ref.mat[i][j]) > 1e-9) {
                    allZero = false;
                    break;
                }
            }
            if (!allZero) {
                rank++;
            }
        }
        return rank;
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(8) << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    double trace() const {
        if (rows != cols)
            throw std::invalid_argument("Trace is only defined for square matrices");
        
        double trace = 0;
        for (int i = 0; i < rows; i++) {
            trace += mat[i][i];
        }
        return trace;
    }

    // Determinant (2x2 matrix)
    double determinant() const {
        if (rows == 2 && cols == 2) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        } else {
            throw std::invalid_argument("Determinant calculation is only implemented for 2x2 matrices");
        }
    }

    // Characteristic Polynomial (2x2 matrix)
    void characteristicPolynomial() const {
        if (rows == 2 && cols == 2) {
            double a = mat[0][0];
            double b = mat[0][1];
            double c = mat[1][0];
            double d = mat[1][1];
            double traceA = a + d;
            double detA = determinant();

            std::cout << "Characteristic Polynomial: λ^2 - (" << traceA << ")λ + " << detA << " = 0" << std::endl;
        } else {
            throw std::invalid_argument("Characteristic polynomial is only implemented for 2x2 matrices");
        }
    }

    // Eigenvalues (2x2 matrix)
    std::vector<double> eigenvalues() const {
        if (rows == 2 && cols == 2) {
            double traceA = trace();
            double detA = determinant();
            double term = std::sqrt(traceA * traceA - 4 * detA);

            double lambda1 = (traceA + term) / 2;
            double lambda2 = (traceA - term) / 2;

            return {lambda1, lambda2};
        } else {
            throw std::invalid_argument("Eigenvalue calculation is only implemented for 2x2 matrices");
        }
    }

    // Eigenvectors (2x2 matrix)
    std::vector<std::vector<double>> eigenvectors() const {
        if (rows == 2 && cols == 2) {
            std::vector<double> lambdas = eigenvalues();
            std::vector<std::vector<double>> eigenvectors;

            for (double lambda : lambdas) {
                Matrix A_lambdaI(2, 2);
                A_lambdaI.setElement(0, 0, mat[0][0] - lambda);
                A_lambdaI.setElement(0, 1, mat[0][1]);
                A_lambdaI.setElement(1, 0, mat[1][0]);
                A_lambdaI.setElement(1, 1, mat[1][1] - lambda);

                if (A_lambdaI.getElement(0, 0) != 0 || A_lambdaI.getElement(0, 1) != 0) {
                    eigenvectors.push_back({-A_lambdaI.getElement(0, 1), A_lambdaI.getElement(0, 0)});
                } else {
                    eigenvectors.push_back({-A_lambdaI.getElement(1, 1), A_lambdaI.getElement(1, 0)});
                }
            }
            return eigenvectors;
        } else {
            throw std::invalid_argument("Eigenvector calculation is only implemented for 2x2 matrices");
        }
    }
};

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    Matrix matrix(n, n);

    cout << "Enter elements of the matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double value;
            cin >> value;
            matrix.setElement(i, j, value);
        }
    }

    cout << "Matrix:" << endl;
    matrix.display();

    cout << "Row Echelon Form:" << endl;
    Matrix rowEchelonForm = matrix.rowEchelon();
    rowEchelonForm.display();

    cout << "Rank of the matrix: " << matrix.rank() << endl;

    cout << "Transpose:" << endl;
    Matrix transpose = matrix.transpose();
    transpose.display();

    if (n == 2 || n == 3) { // Small matrices only
        cout << "Determinant: " << matrix.determinant() << endl;

        try {
            cout << "Inverse:" << endl;
            Matrix inverse = matrix.inverse();
            inverse.display();
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
