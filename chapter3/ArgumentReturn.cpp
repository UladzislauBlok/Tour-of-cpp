#include <iostream>
#include <vector>

void test(vector<int> v, vector<int> &rv) // v is passed by value; rv is passed by reference
{
    v[1] = 99; // modify v (a local variable)
    rv[2] = 66; // modify whatever rv refers to
}

int main() {
    std::vector fib = {1, 2, 3, 5, 8, 13, 21};
    test(fib, fib);
    std::cout << fib[1] << ' ' << fib[2] << '\n'; // prints 2 66
}

// we give Matrix a move constructor (§6) that very cheaply moves the Matrix out of operator+().
Matrix operator+(const Matrix &x, const Matrix &y) {
    Matrix res;
    // ... for all res[i,j], res[i,j] = x[i,j]+y[i,j] ...
    return res;
}

Matrix *add(const Matrix &x, const Matrix &y) // complicated and error-prone 20th century style
{
    Matrix *p = new Matrix;
    // ... for all *p[i,j], *p[i,j] = x[i,j]+y[i,j] ...
    return p;
}

auto mul(int i, double d) { return i * d; } // here, "auto" means "deduce the return type"
auto mul(int i, double d) -> double { return i * d; } // the return type is "double"

struct Entry {
    std::string name;
    int value;
};

Entry read_entry(std::istream& is) // naive read function (for a better version, see §11.5)
{
    std::string s;
    int i;
    is >> s >> i;
    return {s,i};
}