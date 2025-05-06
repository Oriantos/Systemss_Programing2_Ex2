//
// Created by dembi on 04/05/2025.
//

#include "SquareMat.h"
#include <cmath>
#include <iomanip>
#include <regex>

namespace Matrix {
    SquareMat::SquareMat(int size, double **data): size(size) {
        if (size <= 0) {
            this->size = 0;
            throw InvalidOperation();
        }
        allocate();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    }

    SquareMat::SquareMat(int size): size(size) {
        if (size <= 0) {
            this->size = 0;
            throw InvalidOperation();
        }
        allocate();
    }


    void SquareMat::allocate() {
        data = new double *[size];
        for (int i = 0; i < size; ++i) {
            data[i] = new double[size]{};
        }
    }

    const void SquareMat::copyFrom(const SquareMat &other) {
        size = other.size;
        allocate();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    SquareMat::SquareMat(const SquareMat &other): size(other.size), data(nullptr) {
        copyFrom(other);
    }

    void SquareMat::deallocate() {
        if (data) {
            for (int i = 0; i < size; ++i) {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
    }

    SquareMat::~SquareMat() {
        deallocate();
    }

    SquareMat &SquareMat::operator=(const SquareMat &other) {
        if (this != &other) {
            deallocate();
            copyFrom(other);
        }
        return *this;
    }

    const double *SquareMat::operator[](int i) const {
        if (i < 0 || i >= size) throw InvalidOperation();
        return data[i];
    }

    double *SquareMat::operator[](int i) {
        if (i < 0 || i >= size) throw InvalidOperation();
        return data[i];
    }

    SquareMat SquareMat::operator+(const SquareMat &other) const {
        if (size != other.size) throw SizeMismatch();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[i][j] + other[i][j];
        return result;
    }

    SquareMat SquareMat::operator-(const SquareMat &other) const {
        if (size != other.size) throw SizeMismatch();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[i][j] - other[i][j];
        return result;
    }

    SquareMat SquareMat::operator-() const {
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = -data[i][j];
        return result;
    }

    SquareMat SquareMat::operator*(const SquareMat &other) const {
        if (size != other.size) throw SizeMismatch();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                for (int k = 0; k < size; ++k)
                    result[i][j] += data[i][k] * other[k][j];
        return result;
    }

    SquareMat SquareMat::operator*(double scalar) const {
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[i][j] * scalar;
        return result;
    }

    SquareMat SquareMat::operator%(const SquareMat &other) const {
        if (size != other.size) throw SizeMismatch();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[i][j] * other[i][j];
        return result;
    }

    SquareMat SquareMat::operator%(int scalar) const {
        if (scalar == 0) throw DivisionByZero();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = std::fmod(data[i][j], scalar);
        return result;
    }

    SquareMat SquareMat::operator/(double scalar) const {
        if (scalar == 0) throw DivisionByZero();
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[i][j] / scalar;
        return result;
    }

    SquareMat SquareMat::operator^(int exp) const {
        if (exp < 0) throw InvalidOperation();
        SquareMat res(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    res[i][j] = 1;
                } else {
                    res[i][j] = 0;
                }
            }
        }
        if (exp == 0) {
            return res;
        }
        SquareMat t(size, data);
        for (int i = 0; i < exp; ++i) {
            res *= t;
        }
        return res;
    }

    SquareMat &SquareMat::operator+=(const SquareMat &other) { return *this = *this + other; }
    SquareMat &SquareMat::operator-=(const SquareMat &other) { return *this = *this - other; }
    SquareMat &SquareMat::operator*=(const SquareMat &other) { return *this = *this * other; }
    SquareMat &SquareMat::operator*=(double scalar) { return *this = *this * scalar; }
    SquareMat &SquareMat::operator%=(const SquareMat &other) { return *this = *this % other; }
    SquareMat &SquareMat::operator%=(int scalar) { return *this = *this % scalar; }
    SquareMat &SquareMat::operator/=(double scalar) { return *this = *this / scalar; }

    SquareMat &SquareMat::operator++() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                ++data[i][j];
        return *this;
    }

    SquareMat SquareMat::operator++(int) {
        SquareMat tmp(*this);
        ++(*this);
        return tmp;
    }

    SquareMat &SquareMat::operator--() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                --data[i][j];
        return *this;
    }

    SquareMat SquareMat::operator--(int) {
        SquareMat tmp(*this);
        --(*this);
        return tmp;
    }

    SquareMat SquareMat::operator~() const {
        SquareMat result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = data[j][i];
        return result;
    }

    double SquareMat::operator!() const {
        if (size == 1) return data[0][0];
        if (size == 2) return D2Det();
        return recDet();
    }

    double SquareMat::D2Det() const {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    double SquareMat::recDet() const {
        double res = 0;
        for (int i = 0; i < size; ++i) {
            SquareMat minor = SquareMat::minor(0, i);
            if (minor.size == 2) {
                res += std::pow(-1, i) * data[0][i] * minor.D2Det();
            } else {
                res += std::pow(-1, i) * data[0][i] * minor.recDet();
            }
        }
        return res;
    }

    SquareMat SquareMat::minor(int col, int row) const {
        SquareMat result(size - 1);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i != col && j != row) {
                    if (i < col && j < row) {
                        result[i][j] = data[i][j];
                    } else if (i > col) {
                        result[i - 1][j] = data[i][j];
                    } else if (j > row) {
                        result[i][j - 1] = data[i][j];
                    } else {
                        result[i - 1][j - 1] = data[i][j];
                    }
                }
            }
        }
        return result;
    }

    bool SquareMat::operator==(const SquareMat &other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (data[i][j] != other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool SquareMat::operator!=(const SquareMat &other) const {
        return !(*this == other);
    }

    bool SquareMat::operator<(const SquareMat &other) const {
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j) {
                sum1 += data[i][j];
                sum2 += other[i][j];
            }
        return sum1 < sum2;
    }

    bool SquareMat::operator<=(const SquareMat &other) const {
        return *this < other || *this == other;
    }

    bool SquareMat::operator>(const SquareMat &other) const {
        return !(*this <= other);
    }

    bool SquareMat::operator>=(const SquareMat &other) const {
        return !(*this < other);
    }

    std::ostream &operator<<(std::ostream &out, const SquareMat &mat) {
        for (int i = 0; i < mat.size; ++i) {
            for (int j = 0; j < mat.size; ++j) {
                out << mat[i][j];
                if (j < mat.size - 1) out << " ";
            }
            out << "\n";
        }
        return out;
    }
} // Matrix
