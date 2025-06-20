/*
C++ supports two notions of immutability (an object with an unchangeable state):
• const: meaning roughly ‘I promise not to change this value.’
    This is used primarily to specify interfaces so that data can be passed to functions using pointers and references without fear of it being modified.
    The compiler enforces the promise made by const. The value of a const may be calculated at run time.
• constexpr: meaning roughly ‘to be evaluated at compile time.’
    This is used primarily to specify constants, to allow placement of data in read-only memory (where it is unlikely to be corrupted), and for performance.
    The value of a constexpr must be calculated by the compiler.
*/

#include <cmath>
#include <vector>
constexpr int dmv = 17; // dmv is a named constant
int var = 17; // var is not a constant
const double sqv = std::sqrt(var); // sqv is a named constant, possibly computed at run time
double sum(const std::vector<double>&); // sum will not modify its argument (§1.7)
std::vector<double> v {1.2, 3.4, 4.5}; // v is not a constant
const double s1 = sum(v); // OK: sum(v) is evaluated at run time
constexpr double s2 = sum(v); // error: sum(v) is not a constant expression

constexpr double square(double x) { return x * x; }
constexpr double max1 = 1.4 * square(17); // OK: 1.4*square(17) is a constant expression
constexpr double max2 = 1.4 * square(var); // error: var is not a constant, so square(var) is not a constant
const double max3 = 1.4 * square(var); // OK: may be evaluated at run time

/*
A constexpr function can be used for non-constant arguments, but when that is done the result is not a constant expression.
We allow a constexpr function to be called with non-constant-expression arguments in contexts that do not require constant expressions.
That way, we don’t have to define essentially the same function twice: once for constant expressions and once for variables.
When we want a function to be used only for evaluation at compile time, we declare it consteval rather than constexpr.
*/

consteval double square2(double x) { return x * x; }
constexpr double max1 = 1.4 * square2(17); // OK: 1.4*square2(17) is a constant expression
const double max3 = 1.4 * square2(var); // error: var is not a constant

constexpr double nth(double x, int n) // assume 0<=n
{
    double res = 1;
    int i = 0;
    while (i<n) { // while-loop: do while the condition is true (§1.7.1)
        res *= x;
        ++i;
    }
    return res;
}


