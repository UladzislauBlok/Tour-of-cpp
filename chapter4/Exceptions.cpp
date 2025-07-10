#include <stdexcept>

double &Vector::operator[](int i) {
    if (!(0 <= i && i < size()))
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

void f(Vector &v) {
    // ...
    try {
        // out_of_range exceptions thrown in this block are handled by the handler defined below
        compute1(v); // might try to access beyond the end of v
        Vector v2 = compute2(v); // might try to access beyond the end of v
        compute3(v2); // might try to access beyond the end of v2
    } catch (const out_of_range &err) {
        // oops: out_of_range error
        // ... handle range error ...
        cerr << err.what() << '\n';
    }
    // ...
}
