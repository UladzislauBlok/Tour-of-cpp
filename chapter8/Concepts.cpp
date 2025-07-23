#include <ranges>

template<typename Sequence, typename Value>
Value sum(const Sequence& s, Value v) {
    for (const auto& x : s)
        v+=x;
    return v;
}
// This sum() requires that
// • its first template argument is some kind of sequence of elements, and
// • its second template argument is some kind of number.
// To be more specific, sum() can be invoked for a pair of arguments:
// • A sequence, Seq, that supports begin() and end() so that the range-for will work (§1.7; §14.1).
// • An arithmetic type, Value, that supports += so that elements of the sequence can be added.
// We call such requirements concepts.

// sum() again:
template<Sequence Seq, Number Num>
    requires Arithmetic<std::ranges::range_value_t<Seq>,Num>
Num sum(const Seq& s, Num n);

template<Sequence Seq, Number Num>
Num sum(const Seq& s, Num v) {
    for (const auto& x : s)
        v+=x;
    return v;
}

// Concept-based Overloading
template<forward_iterator Iter>
void advance(Iter p, int n) { // move p n elements forward
    while (n--)
        ++p; // a forward iterator has ++, but not + or +=
}
template<random_access_iterator Iter>
void advance(Iter p, int n) { // move p n elements forward
    p+=n; // a random-access iterator has +=
}
// The compiler will select the template with the strongest requirements met by the arguments.
// In this case, a list only supplies forward iterators, but a vector offers random-access iterators, so we get:
void user(vector<int>::iterator vip, list<string>::iterator lsp) {
    advance(vip,10); // uses the fast advance()
    advance(lsp,10); // uses the slow advance()
}

// Consider first a single argument for several alternative functions:
// • If the argument doesn’t match the concept, that alternative cannot be chosen.
// • If the argument matches the concept for just one alternative, that alternative is chosen.
// • If arguments from two alternatives match a concept and one is stricter than the other
// (match all the requirements of the other and more), that alternative is chosen.
// • If arguments from two alternatives are equally good matches for a concept, we have an ambiguity.
// For an alternative to be chosen it must be
// • a match for all of its arguments, and
// • at least an equally good match for all arguments as other alternatives, and
// • a better match for at least one argument.

// Definition of Concepts
template<typename T>
concept Equality_comparable =
requires (T a, T b) {
    { a == b } -> Boolean; // compare Ts with ==
    { a != b } -> Boolean; // compare Ts with !=
};

static_assert(Equality_comparable<int>); // succeeds
struct S { int a; };
static_assert(Equality_comparable<S>); // fails because structs don’t automatically get == and !=

// Defining Equality_comparable to handle nonhomogeneous comparisons is almost as easy:
template<typename T, typename T2 =T>
concept Equality_comparable =
requires (T a, T2 b) {
    { a == b } -> Boolean; // compare a T to a T2 with ==
    { a != b } -> Boolean; // compare a T to a T2 with !=
    { b == a } -> Boolean; // compare a T2 to a T with ==
    { b != a } -> Boolean; // compare a T2 to a T with !=
};

static_assert(Equality_comparable<int,double>); // succeeds
static_assert(Equality_comparable<int>); // succeeds (T2 is defaulted to int)
static_assert(Equality_comparable<int,string>); // fails

template<typename T, typename U = T>
concept Number =
requires(T x, U y) { // Something with arithmetic operations and a zero
    x+y; x-y; x*y; x/y;
    x+=y; x-=y; x*=y; x/=y;
    x=x; // copy
    x=0;
};

template<typename T, typename U = T>
concept Arithmetic = Number<T,U> && Number<U,T>;

template<typename S>
concept Sequence = requires (S a) {
    typename range_value_t<S>; // S must have a value type
    typename iterator_t<S>; // S must have an iterator type
    { a.begin() } -> same_as<iterator_t<S>>; // S must have a begin() that returns an iterator
    { a.end() } -> same_as<iterator_t<S>>;
    requires input_iterator<iterator_t<S>>; // S’s iterator must be an input_iterator
    requires same_as<range_value_t<S>, iter_value_t<S>>;
};

// In particular, there is a standard-library concept that allows us to bypass the complexity of the definition of Sequence:
template<typename S>
concept Sequence = input_range<S>; // simple to write and general
// Had I restricted my notion of ‘S’s value type to S::value_type, I could have used a simple Value_type:
template<class S>
using Value_type = typename S::value_type;
// That’s a useful technique for expressing simple notions concisely and for hiding complexity. The
// definition of the standard value_type_t is fundamentally similar, but a bit more complicated because
// it handles sequences that don’t have a member called value_type (e.g., built-in arrays).

template<equality_comparable T>
bool cmp(T a, T b){
    return a<b;
}
// Here the concept guarantees the presence of == but not <:
bool b0 = cmp(cout,cerr); // error: ostream doesn’t support ==
bool b1 = cmp(2,3); // OK: returns true
bool b2 = cmp(2+3i,3+4i); // error: complex<double> doesn’t support <

// Delaying the final check of the template definition until instantiation time gives two benefits:
// • We can use incomplete concepts during development. That allows us to gain experience
// while developing concepts, types, and algorithms, and to gradually improve checking.
// • We can insert debug, tracing, telemetry, etc. code into a template without affecting its interface.
// Changing an interface can cause massive recompilation.

// The keyword auto can be used to indicate that an object should have the type of its initializer:
auto x = 1; // x is an int
auto z = complex<double>{1,2}; // z is a complex<double>
// However, initialization doesn’t just take place in the simple variable definitions:
auto g() { return 99; } // g() returns an int
int f(auto x) { /* ... */ } // take an argument of any type
int x = f(1); // this f() takes an int
int z = f(complex<double>{1,2}); // this f() takes a complex<double>
// The keyword auto denotes the least constrained concept for a value: it simply requires that it must
// be a value of some type. Taking an auto parameter makes a function into a function template.

auto twice(Arithmetic auto x) { return x+x; } // just for numbers
auto thrice(auto x) { return x+x+x; } // for anything with a +
auto x1 = twice(7); // OK: x1==14
string s = "Hello";
auto x2 = twice(s); // error: a string is not Arithmetic
auto x3 = thrice(s); // OK x3=="Hello Hello Hello "
// In addition to their use for constraining function arguments, concepts can constrain the initialization of variables:
auto ch1 = open_channel("foo"); // works with whatever open_channel() returns
Arithmetic auto ch2 = open_channel("foo"); // error: a channel is not Arithmetic
Channel auto ch3 = open_channel("foo"); // OK: assuming Channel is an appropriate concept and that open_channel() returns one

// Concepts and Types

// A type:
// • Specifies the set of operations that can be applied to an object, implicitly and explicitly
// • Relies on function declarations and language rules
// • Specifies how an object is laid out in memory

// A single-argument concept:
// • Specifies the set of operations that can be applied to an object, implicitly and explicitly
// • Relies on use patterns reflecting function declarations and language rules
// • Says nothing about the layout of the object
// • Enables the use of a set of types


