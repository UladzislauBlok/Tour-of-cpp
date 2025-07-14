// We can define operators for user-defined types (classes and enumerations):
// • Binary arithmetic operators: +, -, ∗, /, and %
// • Binary logical operators: & (bitwise and), | (bitwise or), and ˆ (bitwise exclusive or)
// • Binary relational operators: ==, !=, <, <=, >, >=, and <=>
// • Logical operators: && and ||
// • Unary arithmetic and logical operators: +, -, ˜ (bitwise complement), and ! (logical negation)
// • Assignments: =, +=, ∗=, etc.
// • Increments and decrements: ++ and --
// • Pointer operations: ->, unary ∗, and unary &
// • Application (call): ()
// • Subscripting: []
// • Comma: ,
// • Shift: >> and <<

class Matrix {
    // ...
    Matrix &operator=(const Matrix &a); // assign m to *this; return a reference to *this
};

Matrix operator+(const Matrix &m1, const Matrix &m2); // assign m1 to m2 and return the sum

// Conventional Operations
// • Comparisons: ==, !=, <, <=, >, >=, and <=>
// • Container operations: size(), begin(), and end()
// • Iterators and ‘smart pointers’: ->, ∗, [], ++, --, +, -, +=, and -=
// • Function objects: ()
// • Input and output operations: >> and <<
// • swap()
// • Hash functions: hash<>

// The meaning of the equality comparisons (== and !=) is closely related to copying.
// After a copy, the copies should compare equal:
void f() {
    X a = something;
    X b = a;
    assert(a == b); // if a!=b here, something is very odd
}

// When defining ==, also define != and make sure that a!=b means !(a==b).
// Similarly, if you define <, also define <=, >, >= to make sure that the usual equivalences hold:
// • a<=b means (a<b)||(a==b) and !(b<a).
// • a>b means b<a.
// • a>=b means (a>b)||(a==b) and !(a<b).
// To give identical treatment to both operands of a binary operator, such as ==, it is best defined as a
// free-standing function in the namespace of its class. For example:
namespace NX {
    class X {
        // ...
    };

    bool operator==(const X &, const X &);

    // ...
};

// by defining the default <=> the other relational operators are implicitly defined:
class R {
    // ...
    auto operator<=>(const R &a) const = default;
};

void user(R r1, R r2) {
    bool b1 = (r1 <=> r2) == 0; // r1==r2
    bool b2 = (r1 <=> r2) < 0; // r1<r2
    bool b3 = (r1 <=> r2) > 0; // r1>r2
    bool b4 = (r1 == r2);
    bool b5 = (r1 < r2);
}

// If <=> is defined as non-default, == is not implicitly defined, but < and the other relational operators are! For example:
struct R2 {
    int m;
    auto operator<=>(const R2 &a) const { return a.m == m ? 0 : a.m < m ? -1 : 1; }
};

void user(R2 r1, R2 r2) {
    bool b4 = (r1 == r2); // error: no non-default ==
    bool b5 = (r1 < r2); // OK
}

// This leads to this pattern of definition for nontrivial types:
struct R3 {
    /* ... */
};

auto operator<=>(const R3 &a, const R3 &b) {
    /* ... */
}

bool operator==(const R3 &a, const R3 &b) {
    /* ... */
}

// The standard-library containers all know their number of elements and we can obtain it by calling size(). For example:
void f1() {
    for (size_t i = 0; i != c.size(); ++i) // size_t is the name of the type returned by a standard-library size()
        c[i] = 0;
}

// However, rather than traversing containers using indices from 0 to size(), the standard algorithms rely on the notion of sequences delimited by pairs of iterators:
void f1() {
    for (auto p = c.begin(); p != c.end(); ++p)
        *p = 0;
}

// These begin() and end() functions are also used by the implementation of the range-for, so we can simplify loops over a range:
void f2() {
    for (auto &x: c)
        x = 0;
    // Iterators are used to pass sequences to standard-library algorithms. For example:
    sort(v.begin(), v.end());
}

// User-Defined Literals
// The i for imaginary suffix might be implemented like this:
constexpr complex<double> operator""i(long double arg) // imaginary literal
{
    return {0, arg};
}

// Here
// • The operator"" indicates that we are defining a literal operator.
// • The i after the literal indicator, "", is the suffix to which the operator gives a meaning.
// • The argument type, long double, indicates that the suffix (i) is being defined for a floating-
// point literal.
// • The return type, complex<double>, specifies the type of the resulting literal.
// Given that, we can write
complex<double> z = 2.7182818 + 6.283185i;
