#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Tests.h"
#include "SquareMat.h"
#include <sstream>
using namespace Matrix;

// Helpers

double** make_matrix(int n, std::initializer_list<std::initializer_list<double>> init) {
    double** arr = new double*[n];
    int i = 0;
    for (auto& row : init) {
        arr[i] = new double[n];
        int j = 0;
        for (auto& val : row) {
            arr[i][j++] = val;
        }
        ++i;
    }
    return arr;
}

void delete_matrix(double** arr, int n) {
    for (int i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;
}

// ================= TEST CASES ===================

TEST_CASE("Addition") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{4.0, 3.0}, {2.0, 1.0}});
    auto e = make_matrix(n, {{5.0, 5.0}, {5.0, 5.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    CHECK((A + B) == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

TEST_CASE("Subtraction") {
    int n = 2;
    auto a = make_matrix(n, {{5.0, 5.0}, {5.0, 5.0}});
    auto b = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{4.0, 3.0}, {2.0, 1.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    CHECK((A - B) == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

TEST_CASE("Unary minus") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, -2.0}, {-3.0, 4.0}});
    auto e = make_matrix(n, {{-1.0, 2.0}, {3.0, -4.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((-A) == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Matrix multiplication") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{2.0, 0.0}, {1.0, 2.0}});
    auto e = make_matrix(n, {{4.0, 4.0}, {10.0, 8.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    CHECK((A * B) == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

TEST_CASE("Scalar multiplication and division") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{2.0, 4.0}, {6.0, 8.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((A * 2.0) == E);
    CHECK((2.0 * A) == E);
    CHECK((E / 2.0) == A);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Modulo (scalar and elementwise)") {
    int n = 2;
    auto a = make_matrix(n, {{5.0, 7.0}, {10.0, 13.0}});
    auto e = make_matrix(n, {{2.0, 1.0}, {1.0, 1.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((A % 3) == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Element-wise multiplication") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{5.0, 6.0}, {7.0, 8.0}});
    auto e = make_matrix(n, {{5.0, 12.0}, {21.0, 32.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    CHECK((A % B) == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

TEST_CASE("Power operator ^") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{7.0, 10.0}, {15.0, 22.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((A ^ 2) == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Transpose") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{1.0, 3.0}, {2.0, 4.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((~A) == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Determinant") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    SquareMat A(n, a);
    CHECK(doctest::Approx(!A) == -2.0);
    delete_matrix(a, n);
}

TEST_CASE("Increment/Decrement") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 1.0}, {1.0, 1.0}});
    auto e = make_matrix(n, {{2.0, 2.0}, {2.0, 2.0}});
    SquareMat A(n, a), E(n, e);
    CHECK((++A) == E);
    SquareMat B = A--;
    CHECK(B == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

TEST_CASE("Element access") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    SquareMat A(n, a);
    A[0][0] = 9.0;
    CHECK(A[0][0] == 9.0);
    CHECK(A[1][1] == 4.0);
    delete_matrix(a, n);
}

TEST_CASE("Comparison operators") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{4.0, 3.0}, {2.0, 1.0}});
    auto c = make_matrix(n, {{5.0, 5.0}, {5.0, 5.0}});
    SquareMat A(n, a), B(n, b), C(n, c);
    CHECK(A == B);
    CHECK(A != C);
    CHECK(C > A);
    CHECK(A < C);
    CHECK(C >= B);
    CHECK(B <= C);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(c, n);
}

TEST_CASE("Compound operators") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{4.0, 3.0}, {2.0, 1.0}});
    auto e = make_matrix(n, {{5.0, 5.0}, {5.0, 5.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    A += B;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

TEST_CASE("Stream output") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    SquareMat A(n, a);
    std::ostringstream oss;
    oss << A;
    CHECK(oss.str().find("1.0") != std::string::npos);
    delete_matrix(a, n);
}

TEST_CASE("Compound subtraction operator -=") {
    int n = 2;
    auto a = make_matrix(n, {{5.0, 5.0}, {5.0, 5.0}});
    auto b = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{4.0, 3.0}, {2.0, 1.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    A -= B;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

// Compound: *= scalar
TEST_CASE("Compound scalar multiplication operator *=") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto e = make_matrix(n, {{2.0, 4.0}, {6.0, 8.0}});
    SquareMat A(n, a), E(n, e);
    A *= 2.0;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

// Compound: /= scalar
TEST_CASE("Compound scalar division operator /=") {
    int n = 2;
    auto a = make_matrix(n, {{2.0, 4.0}, {6.0, 8.0}});
    auto e = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    SquareMat A(n, a), E(n, e);
    A /= 2.0;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

// Compound: %= scalar
TEST_CASE("Compound scalar modulo operator %=") {
    int n = 2;
    auto a = make_matrix(n, {{5.0, 7.0}, {10.0, 13.0}});
    auto e = make_matrix(n, {{2.0, 1.0}, {1.0, 1.0}});
    SquareMat A(n, a), E(n, e);
    A %= 3;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(e, n);
}

// Compound: %= matrix
TEST_CASE("Compound matrix element-wise modulo operator %=") {
    int n = 2;
    auto a = make_matrix(n, {{10.0, 9.0}, {8.0, 7.0}});
    auto b = make_matrix(n, {{3.0, 2.0}, {3.0, 2.0}});
    auto e = make_matrix(n, {{1.0, 1.0}, {2.0, 1.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    A %= B;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}

// Compound: *= matrix
TEST_CASE("Compound matrix multiplication operator *=") {
    int n = 2;
    auto a = make_matrix(n, {{1.0, 2.0}, {3.0, 4.0}});
    auto b = make_matrix(n, {{2.0, 0.0}, {1.0, 2.0}});
    auto e = make_matrix(n, {{4.0, 4.0}, {10.0, 8.0}});
    SquareMat A(n, a), B(n, b), E(n, e);
    A *= B;
    CHECK(A == E);
    delete_matrix(a, n); delete_matrix(b, n); delete_matrix(e, n);
}
