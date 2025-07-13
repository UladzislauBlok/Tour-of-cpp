class complex {
    double re, im; // representation: two doubles
public:
    complex(double r, double i) : re{r}, im{i} {
    } // construct complex from two scalars

    complex(double r) : re{r}, im{0} {
    } // construct complex from one scalar

    complex() : re{0}, im{0} {
    } // default complex: {0,0}

    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    complex &operator+=(complex z) {
        re += z.re; // add to re and im
        im += z.im;
        return *this; // return the result
    }

    complex &operator-=(complex z) {
        re -= z.re;
        im -= z.im;
        return *this;
    }

    complex &operator *=(complex); // defined out-of-class somewhere
    complex &operator/=(complex); // defined out-of-class somewhere
};

complex z = {1, 0};
const complex cz{1, 3};
// z = cz; // OK: assigning to a non-const variable
// cz = z; // error: assignment to a const
double x = z.real(); // OK: complex::real() is const

complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; } // unary minus
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

bool operator==(complex a, complex b) { return a.real() == b.real() && a.imag() == b.imag(); } // equal
bool operator!=(complex a, complex b) { return !(a == b); } // not equal

void f(complex z) {
    complex a{2.3}; // construct {2.3,0.0} from 2.3
    complex b{1 / a};
    complex c{a + z * complex{1, 2.3}};
    if (c != b)
        c = -(b / a) + 2 * b;
}
