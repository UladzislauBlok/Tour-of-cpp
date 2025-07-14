class X {
public:
    X (Sometype); // ‘ordinary constructor’: create an object
    X(); // default constructor
    X(const X &); // copy constructor
    X(X &&); // move constructor
    X &operator=(const X &); // copy assignment: clean up target and copy
    X &operator=(X &&); // move assignment: clean up target and move
    ˜X(); // destructor: clean up
    // ...
};

// Here, a compiler will typically construct the X from make() directly in x; thus eliminating (‘eliding’) a copy.
X make(Sometype);
X x = make(value);


// If you are explicit about some defaults, other default definitions will not be generated
class Y {
public:
    Y (Sometype);

    Y(const Y &) = default; // I really do want the default copy constructor
    Y(Y &&) = default; // and the default move constructor
    // ...
};

// A good rule of thumb (sometimes called the rule of zero) is to either define all of the essential operations or none (using the default for all). For example:
struct Z {
    Vector v;
    string s;
};

Z z1; // default initialize z1.v and z1.s
Z z2 = z1; // default copy z1.v and z1.s

// To complement =default, we have =delete to indicate that an operation is not to be generated.
// A base class in a class hierarchy is the classic example where we don’t want to allow a memberwise copy.
class Shape {
public:
    Shape(const Shape &) = delete; // no copying
    Shape &operator=(const Shape &) = delete;

    // ...
};

void copy(Shape &s1, const Shape &s2) {
    s1 = s2; // error: Shape copy is deleted
}

// Member Initializers
class complex {
    double re = 0;
    double im = 0; // representation: two doubles with default value 0.0
public:
    complex(double r, double i) : re{r}, im{i} {
    } // construct complex from two scalars: {r,i}
    complex(double r) : re{r} {
    } // construct complex from one scalar: {r,0}
    complex() {
    } // default complex: {0,0}
    // ...
}
