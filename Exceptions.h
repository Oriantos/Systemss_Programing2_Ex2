//
// Created by dembi on 04/05/2025.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <exception>

namespace Matrix {

    class InvalidOperation : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Invalid matrix operation.";
        }
    };

    class SizeMismatch : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Matrix size mismatch.";
        }
    };

    class InvalidSize : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Matrix size invalid.";
        }
    };

    class DivisionByZero : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Division by zero.";
        }
    };

} // namespace Matrix

#endif // MATRIX_EXCEPTIONS_H


#endif //EXCEPTIONS_H
