// A constructor taking a single argument defines a conversion from its argument type. For example, complex provides a constructor from a double:
complex z1 = 3.14; // z1 becomes {3.14,0.0}
complex z2 = z1*2; // z2 becomes z1*{2.0,0} == {6.28,0.0}

// This implicit conversion is sometimes ideal, but not always. For example, Vector provides a constructor from an int:
Vector v1 = 7; // OK: v1 has 7 elements

class Vector {
public:
    explicit Vector(int s); // no implicit conversion from int to Vector
    // ...
};
// That gives us:
Vector v1(7); // OK: v1 has 7 elements
Vector v2 = 7; // error: no implicit conversion from int to Vector
// When it comes to conversions, more types are like Vector than are like complex,
// so use explicit for constructors that take a single argument unless there is a good reason not to.