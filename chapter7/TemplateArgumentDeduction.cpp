#include <string>
#include <utility>
// When defining a type as an instantiation of a template we must specify its template arguments.
std::pair<int, double> p = {1, 5.2};

// We can simply let pair’s constructor deduce the template arguments from an initializer:
std::pair p1 = {1, 5.2}; // p is a pair<int,double>
// Containers provide another example:
template<typename T>
class Vector {
public:
    Vector(int);

    Vector (initializer_list<T>); // initializer-list constructor
    // ...
};

Vector v1{1, 2, 3}; // deduce v1’s element type from the initializer element type: int
Vector v2 = v1; // deduce v2’s element type from v1’s element type: int
auto p = new Vector{1, 2, 3}; // p is a Vector<int>*
Vector<int> v3(1); // here we need to be explicit about the element type (no element type is mentioned)

// However, it is not a panacea. Like all other powerful mechanisms, deduction can cause surprises. Consider:
Vector<std::string> vs{"Hello", "World"}; // OK: Vector<string>
Vector vs1{"Hello", "World"}; // OK: deduces to Vector<const char[6]> (Surprise?)
Vector vs2{"Hello"s, "World"s}; // OK: deduces to Vector<string>
Vector vs3{"Hello"s, "World"}; // error: the initializer list is not homogenous
Vector<std::string> vs4{"Hello"s, "World"}; // OK: the element type is explicit

// Sometimes, we need to resolve an ambiguity.
class Vector {
public:
    Vector (initializer_list<T>); // initializer-list constructor
    template<typename Iter>
    Vector(Iter b, Iter e); // [b:e) iterator-pair constructor
    struct iterator {
        using value_type = T; /* ... */
    };

    iterator begin();

    // ...
};

Vector v1{1, 2, 3, 4, 5}; // element type is int
Vector v2(v1.begin(), v1.begin() + 2); // a pair of iterators or a pair of values (of type iterator)?
Vector v3(9, 17); // error: ambiguous

// Standard library and many other important bodies of code were written decades before we had language support for concepts.
// For those, we need a way of saying ‘a pair of values of the same type should be considered iterators.’
// Adding a 'deduction guide' after the declaration of Vector does exactly that:
template<typename Iter>
Vector(Iter, Iter) -> Vector<typename Iter::value_type>;

// Now we have:
Vector v1{1, 2, 3, 4, 5}; // element type is int
Vector v2(v1.begin(), v1.begin() + 2); // pair-of-iterators: element type is int
Vector v3{v1.begin(), v1.begin() + 2}; // element type is Vector2::iterator

// The {} initializer syntax always prefers the initializer_list constructor (if present), so v3 is a vector of iterators: Vector<Vector<int>::iterator>.
// The () initialization syntax is conventional for when we don’t want an initializer_list.
// The effects of deduction guides are often subtle, so it is best to design class templates so that deduction guides are not needed.
// People who like acronyms refer to 'class template argument deduction' as CTAD