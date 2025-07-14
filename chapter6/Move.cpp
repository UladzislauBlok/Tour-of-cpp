Vector operator+(const Vector &a, const Vector &b) {
    if (a.size() != b.size())
        throw Vector_size_mismatch{};
    Vector res(a.size());
    for (int i = 0; i != a.size(); ++i)
        res[i] = a[i] + b[i];
    return res;
}

// Returning from a + involves copying the result out of the local variable res and into some place
// where the caller can access it. We might use this + like this:
void f(const Vector &x, const Vector &y, const Vector &z) {
    Vector r;
    // ...
    r = x + y + z;
    // ...
}

// That would be copying a Vector at least twice (one for each use of the + operator).
// If a Vector is large, say, 10,000 doubles, that could be embarrassing

// We didn’t really want a copy; we just wanted to get the result out of a function: we wanted to move a Vector rather than copy it.
class Vector {
    // ...
    Vector(const Vector &a); // copy constructor
    Vector &operator=(const Vector &a); // copy assignment
    Vector(Vector &&a); // move constructor
    Vector &operator=(Vector &&a); // move assignment
};

// As is typical, Vector’s move constructor is trivial to define:
Vector::Vector(Vector &&a)
    : elem{a.elem}, // "grab the elements" from a
      sz{a.sz} {
    a.elem = nullptr; // now a has no elements
    a.sz = 0;
}

// The && means ‘rvalue reference’ and is a reference to which we can bind an rvalue. The word ‘rvalue’ is intended to complement ‘lvalue,’
// which roughly means ‘something that can appear on the left-hand side of an assignment’.
// So an rvalue is – to a first approximation – a value that you can’t assign to, such as an integer returned by a function call.
// Thus, an rvalue reference is a reference to something that nobody else can assign to, so we can safely ‘steal’ its value.
// The res local variable in operator+() for Vectors is an example.

// A move constructor does not take a const argument: after all, a move constructor is supposed to
// remove the value from its argument. A move assignment is defined similarly.

// After a move, the moved-from object should be in a state that allows a destructor to be run.

// Where the programmer knows that a value will not be used again, but the compiler can’t be
// expected to be smart enough to figure that out, the programmer can be specific:
Vector f() {
    Vector x(1000);
    Vector y(2000);
    Vector z(3000);
    z = x; // we get a copy (x might be used later in f())
    y = std::move(x); // we get a move (move assignment)
    // ... better not use x here ...
    return z; // we get a move
}

// The standard-library function move() doesn’t actually move anything. Instead, it returns a reference
// to its argument from which we may move – an rvalue reference; it is a kind of cast
