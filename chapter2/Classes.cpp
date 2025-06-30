#include <iostream>
/*
The interface of a class is defined by its public members, and its private members are accessible only through that interface.
The public and private parts of a class declaration can appear in any order,
but conventionally we place the public declarations first and the private declarations later,
except when we want to emphasize the representation
*/
class Vector {
public:
    // Constructor
    // we first initialize elem with a pointer to s elements of type double obtained from the free store. Then, we initialize sz to s.
    Vector(int s) : elem{new double[s]}, sz{s} {} // construct a Vector

    // Access to elements is provided by a subscript function, called operator[].
    // It returns a reference to the appropriate element (a double& allowing both reading and writing).
    double &operator[](int i) { return elem[i]; } // element access: subscripting

    // The size() function is supplied to give users the number of elements.
    int size() { return sz; }

private:
    double *elem; // pointer to the elements
    int sz; // the number of elements
};

// Given that, we can define a variable of our new type Vector:
Vector v(6); // a Vector with 6 elements

/*
Here, the representation of a Vector (the members elem and sz) is accessible only through the interface provided by the public members:
Vector(), operator[](), and size().
*/
double read_and_sum(int s) {
    Vector v(s); // make a vector of s elements
    for (int i = 0; i != v.size(); i++)
        std::cin >> v[i]; // read into elements
    double sum = 0;
    for (int i = 0; i != v.size(); i++)
        sum += v[i]; // take the sum of the elements
    return sum;
}
