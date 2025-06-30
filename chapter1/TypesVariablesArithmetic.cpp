/*
A declaration is a statement that introduces an entity into the program and specifies its type:
• A type defines a set of possible values and a set of operations (for an object).
• An object is some memory that holds a value of some type.
• A value is a set of bits interpreted according to a type.
• A variable is a named object
*/

//bool Boolean, possible values are true and false
//char character, for example, 'a', 'z', and '9'
//int integer, for example, -273, 42, and 1066
//double double-precision floating-point number, for example, -273.15, 3.14, and 6.626e-34
//unsigned non-negative integer, for example, 0, 1, and 999 (use for bitwise logical operations)

// ----------

// Arithmetic:
// x+y
// +x unary plus
// x-y minus
// -x unary minus
// x∗y multiply
// x/y divide
// x%y remainder (modulus) for integers

// Comparison:
// x==y equal
// x!=y not equal
// x<y less than
// x>y greater than
// x<=y less than or equal
// x>=y greater than or equal

// Logical:
// x&y  bitwise and
// x|y  bitwise or
// xˆy  bitwise exclusive or
// ˜x bitwise complement
// x&&y logical and
// x||y logical or
// !x logical not (negation

#include <complex>
#include <vector>

void some_function() // function that doesn’t return a value
{
    double d = 2.2; // initialize floating-point number
    int i = 7; // initialize integer
    d = d + i; // assign sum to d
    i = d * i; // assign product to i; beware: truncating the double d*i to an int
}

// Modifying:
// x+=y
// ++x / x++
// x-=y
// --x / x--
// x∗=y
// x/=y
// x%=y

// ----------

// Initialization:
double d1 = 2.3; // initialize d1 to 2.3
double d2{2.3}; // initialize d2 to 2.3
double d3 = {2.3}; // initialize d3 to 2.3 (the = is optional with { ... })
std::complex<double> z = 1; // a complex number with double-precision floating-point scalars
std::complex<double> z2{d1, d2};
std::complex<double> z3 = {d1, d2}; // the = is optional with { ... }
std::vector<int> v {1, 2, 3, 4, 5, 6}; // a vector of ints

// {} is better then =
// int i1 = 7.8; i1 becomes 7 (surprise?)
// int i2 {7.8}; error: floating-point to integer conversion

// Auto:
/*
Auto:
We use auto where we don’t have a specific reason to mention the type explicitly. ‘Specific reasons’ include:
• The definition is in a large scope where we want to make the type clearly visible to readers of our code.
• The type of the initializer isn’t obvious.
• We want to be explicit about a variable’s range or precision (e.g., double rather than float).
*/
auto b = true; // a bool
auto ch = 'x'; // a char
auto i = 123; // an int
auto d = 1.2; // a double
auto z = sqrt(y); // z has the type of whatever sqrt(y) returns
auto bb{true}; // bb is a bool
