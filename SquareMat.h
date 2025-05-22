//
// Created by dembi on 04/05/2025.
//

#ifndef SQUAREMAT_H
#define SQUAREMAT_H

#include <iostream>
#include "Exceptions.h"

namespace Matrix {
    class SquareMat {
    private:
        int size;
        double **data;

        void allocate();

        void deallocate();

        const void copyFrom(const SquareMat &other);

        double D2Det() const;

        double recDet() const;

        SquareMat minor(int col, int row) const;

    public:
        SquareMat(int size, double **data);

        SquareMat(const SquareMat &other);

        explicit SquareMat(int size);

        ~SquareMat();

        int getSize() const {
            return size;
        }

        SquareMat &operator=(const SquareMat &other);

        SquareMat &operator=(SquareMat &other);

        double *operator[](int row);

        const double *operator[](int row) const;

        SquareMat operator+(const SquareMat &other) const;

        SquareMat operator-(const SquareMat &other) const;

        SquareMat operator*(const SquareMat &other) const;

        SquareMat operator*(double scalar) const;

        SquareMat operator%(const SquareMat &other) const;

        SquareMat operator%(int scalar) const;

        SquareMat operator/(double scalar) const;

        SquareMat operator^(int exponent) const;

        SquareMat operator-() const;

        SquareMat &operator+=(const SquareMat &other);

        SquareMat &operator-=(const SquareMat &other);

        SquareMat &operator*=(const SquareMat &other);

        SquareMat &operator*=(double scalar);

        SquareMat &operator%=(const SquareMat &other);

        SquareMat &operator%=(int scalar);

        SquareMat &operator/=(double scalar);

        SquareMat &operator++(); // pre-increment
        SquareMat operator++(int); // post-increment
        SquareMat &operator--(); // pre-decrement
        SquareMat operator--(int); // post-decrement

        SquareMat operator~() const; // transpose
        double operator!() const; // determinant

        bool operator==(const SquareMat &other) const;

        bool operator!=(const SquareMat &other) const;

        bool operator<(const SquareMat &other) const;

        bool operator<=(const SquareMat &other) const;

        bool operator>(const SquareMat &other) const;

        bool operator>=(const SquareMat &other) const;

        friend std::ostream &operator<<(std::ostream &out, const SquareMat &mat);

        friend SquareMat operator*(double scalar, const SquareMat &mat);
    };

    SquareMat operator*(double scalar, const SquareMat &mat);

    std::ostream &operator<<(std::ostream &out, const SquareMat &mat);
} // Matrix

#endif //SQUAREMAT_H
