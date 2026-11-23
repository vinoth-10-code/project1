#include <iostream>
using namespace std;

class Matrix {
private:
    int data[2][2];

public:
    Matrix() {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                data[i][j] = 0;
    }

    void input() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
                cin >> data[i][j];
            }
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < 2; k++)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
        return result;
    }

    int* operator[](int index) {
        return data[index];
    }

    friend ostream& operator<<(ostream& out, const Matrix& m) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                out << m.data[i][j] << " ";
            out << '\n';
        }
        return out;
    }
};

int main() {
    Matrix A, B;

    cout << "Enter elements of Matrix A (2 x 2):\n";
    A.input();

    cout << "\nEnter elements of Matrix B (2 x 2):\n";
    B.input();

    Matrix sum = A + B;
    Matrix product = A * B;

    cout << "\nMatrix A:\n" << A;
    cout << "\nMatrix B:\n" << B;
    cout << "\nAddition (A + B):\n" << sum;
    cout << "\nMultiplication (A * B):\n" << product;

    cout << "\nElement at row 1, column 1 of A: " << A[0][0] << '\n';
    return 0;
}
