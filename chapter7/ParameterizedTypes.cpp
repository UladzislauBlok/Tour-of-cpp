#include <iostream>
#include <list>
#include <stdexcept>
// The template<typename T> prefix makes T a type parameter of the declaration it prefixes.
// It is C++’s version of the mathematical ‘for all T’ or more precisely ‘for all types T.’
template<typename T>
class Vector {
private:
    T *elem; // elem points to an array of sz elements of type T
    int sz;

public:
    explicit Vector(int s); // constructor: establish invariant, acquire resources
    ~Vector() { delete[] elem; } // destructor: release resources
    // ... copy and move operations ...
    T &operator[](int i); // for non-const Vectors
    const T &operator[](int i) const; // for const Vectors (§5.2.1)
    int size() const { return sz; }
};

// The member functions can be defined similarly:
template<typename T>
Vector<T>::Vector(int s) {
    if (s < 0)
        throw std::length_error{"Vector constructor: negative size"};
    elem = new T[s];
    sz = s;
}

template<typename T>
const T &Vector<T>::operator[](int i) const {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

// Given these definitions, we can define Vectors like this:
Vector<char> vc(200); // vector of 200 characters
Vector<std::string> vs(17); // vector of 17 strings
Vector<std::list<int> > vli(45); // vector of 45 lists of integers

// We can use Vectors like this:
void write(const Vector<std::string> &vs) {
    // Vector of some strings
    for (int i = 0; i != vs.size(); ++i)
        std::cout << vs[i] << '\n';
}

// To support the range-for loop for our Vector, we must define suitable begin() and end() functions:
template<typename T>
T *begin(Vector<T> &x) {
    return &x[0]; // pointer to first element or to one-past-the-last element
}

template<typename T>
T *end(Vector<T> &x) {
    return &x[0] + x.size(); // pointer to one-past-the-last element
}

// Given those, we can write:
void write2(Vector<std::string> &vs) { // Vector of some strings
    for (auto &s: vs)
        std::cout << s << '\n';
}
