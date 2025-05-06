#include <iostream>
#include "SquareMat.h"  // Your header file
using namespace Matrix;

int main() {
    try {
        SquareMat mat1({
            {1.0, 2.0},
            {3.0, 4.0}
        });

        SquareMat mat2({
            {5.0, 6.0},
            {7.0, 8.0}
        });

        std::cout << "Matrix 1:\n" << mat1;
        std::cout << "Matrix 2:\n" << mat2;

        std::cout << "Addition:\n" << (mat1 + mat2);
        std::cout << "Subtraction:\n" << (mat2 - mat1);
        std::cout << "Unary minus:\n" << (-mat1);
        std::cout << "Matrix multiplication:\n" << (mat1 * mat2);
        std::cout << "Scalar multiplication:\n" << (mat1 * 2.0);
        std::cout << "Scalar division:\n" << (mat1 / 2.0);
        std::cout << "Element-wise multiplication:\n" << (mat1 % mat2);
        std::cout << "Modulo with scalar:\n" << (mat2 % 3);
        std::cout << "Power (mat1 ^ 2):\n" << (mat1 ^ 2);
        std::cout << "Transpose (~mat1):\n" << ~mat1;
        std::cout << "Determinant (!mat1): " << !mat1 << "\n";

        SquareMat mat3 = mat1;
        ++mat3;
        std::cout << "Pre-increment:\n" << mat3;
        mat3--;
        std::cout << "Post-decrement:\n" << mat3;

        std::cout << "Comparison mat1 == mat1: " << (mat1 == mat1) << "\n";
        std::cout << "Comparison mat1 > mat2: " << (mat1 > mat2) << "\n";

        std::cout << "Access mat1[1][1] (should be 4.0): " << mat1[1][1] << "\n";
        mat3[0][0] = 10.0;
        std::cout << "Updated mat3:\n" << mat3;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
