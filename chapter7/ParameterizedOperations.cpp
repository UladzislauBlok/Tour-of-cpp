// Function Templates

#include <complex.h>

template<typename Sequence, typename Value>
Value sum(const Sequence &s, Value v) {
    for (const auto &x: s)
        v += x;
    return v;
}

void user(Vector<int> &vi, list<double> &ld, vector<std::complex<double> > &vc) {
    int x = sum(vi, 0); // the sum of a vector of ints (add ints)
    double d = sum(vi, 0.0); // the sum of a vector of ints (add doubles)
    double dd = sum(ld, 0.0); // the sum of a list of doubles
    auto z = sum(vc, std::complex{0.0, 0.0}); // the sum of a vector of complex<double>s
}

// Function Objects
// Function object (sometimes called a functor) are objects that can be called like functions

template<typename T>
class Less_than {
    const T val; // value to compare against
public:
    Less_than(const T &v) : val{v} {
    }

    bool operator()(const T &x) const { return x < val; } // call operator
};

// The function called operator() implements the application operator, (), also called ‘function call’ or just ‘call.’
// We can define named variables of type Less_than for some argument type:
Less_than lti{42}; // lti(i) will compare i to 42 using < (i<42)
Less_than lts{"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")
Less_than<string> lts2{"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <

void fct(int n, const string &s) {
    bool b1 = lti(n); // true if n<42
    bool b2 = lts(s); // true if s<"Backus"
    // ...
}

// predicate
template<typename C, typename P>
int count(const C &c, P pred) { // assume that C is a container and P is a predicate on its elements
    int cnt = 0;
    for (const auto &x: c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s) {
    cout << "number of values less than " << x << ": " << count(vec,Less_than{x}) << '\n';
    cout << "number of values less than " << s << ": " << count(lst,Less_than{s}) << '\n';
}