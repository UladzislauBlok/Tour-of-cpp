class Vector {
public:
    Vector(); // default initalize to "empty"; that is, to no elements
    Vector (std::initializer_list<double>); // initialize with a list of doubles
    // ...
    Vector(int s) : elem{new double[s]}, sz{s} // constructor: acquire resources
    {
        for (int i = 0; i != s; ++i) // initialize elements
            elem[i] = 0;
    }

    ˜Vector() { delete[] elem; } // destructor: release resources
    double &operator[](int i);

    void push_back(double); // add element at end, increasing the size by one

    int size() const;

private:
    double *elem; // elem points to an array of sz doubles
    int sz;
};

Vector gv(10); // global variable; gv is destroyed at the end of the program
Vector8 gp = new Vector(100); // Vector on free store; never implicitly destroyed
void fct(int n) {
    Vector v(n);
    // ... use v ...
    {
        Vector v2(2 * n);
        // ... use v and v2 ...
    } // v2 is destroyed here
} // v is destroyed here

Vector read(istream &is) {
    Vector v;
    for (double d; is >> d;) // read floating-point values into d
        v.push_back(d); // add d to v
    return v;
}

Vector v = read(cin); // no copy of Vector elements here, because of move constructor

Vector v1 = {1, 2, 3, 4, 5}; // v1 has 5 elements
Vector v2 = {1.23, 3.45, 6.7, 8}; // v2 has 4 elements

Vector::Vector(std::initializer_list<double> lst) // initialize with a list
    : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    copy(lst.begin(), lst.end(), elem); // copy from lst into elem
}
