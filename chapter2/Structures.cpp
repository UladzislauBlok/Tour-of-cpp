#include <iostream>

struct Vector {
    double* elem; // pointer to elements
    int sz; // number of elements
};

// A variable of type Vector can be defined like this:
Vector v;

// Method to initialize Vector
// Could also be placed inside struct
void vector_init(Vector& v, int s) // initialize a Vector
{
    // The new operator allocates memory from an area called the free store (also known as dynami memory and heap)
    v.elem = new double[s]; // allocate an array of s doubles
    v.sz = s;
}

double read_and_sum(int s)
// read s integers from cin and return their sum; s is assumed to be positive
{
    Vector v;
    vector_init(v, s); // allocate s elements for v
    for (int i = 0; i != s; i++)
        std::cin >> v.elem[i]; // read into elements
    double sum = 0;
    for (int i = 0; i != s; i++)
        sum += v.elem[i]; // compute the sum of the elements
    return sum;
}

// We use . (dot) to access struct members through a name (and through a reference) and -> to access struct members through a pointer
void f(Vector v, Vector &rv, Vector *pv) {
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i3 = pv->sz; // access through pointer
}
