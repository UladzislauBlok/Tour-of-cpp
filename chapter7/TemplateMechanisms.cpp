// To define good templates, we need some supporting language facilities:
// • Values dependent on a type: variable templates (§7.4.1).
// • Aliases for types and templates: alias templates (§7.4.2).
// • A compile-time selection mechanism: if constexpr (§7.4.3).
// • A compile-time mechanism to inquire about properties of types and expressions: requires-expressions.
// In addition, constexpr functions (§1.6) and static_asserts (§4.5.2) often take part in template design and use

// When we define a C<T>, we often want constants and variables of type C<T> and other types depending on T
template<typename T, typename T2>
constexpr bool Assignable = is_assignable<T &, T2>::value; // is_assignable is a type trait (§16.4.1)
template<typename T>
void testing() {
    static_assert(Assignable<T &, double>, "can't assign a double to a T");
    static_assert(Assignable<T &, string>, "can't assign a string to a T");
}

// Naturally, we can use arbitrary expressions of suitable types as initializers

// It is useful to introduce a synonym for a type or a template.
// For example, the standard header <cstddef> contains a definition of the alias size_t, maybe: using size_t = unsigned int;
// The actual type named size_t is implementation-dependent, so in another implementation size_t may be an unsigned long.

// It is very common for a parameterized type to provide an alias for types related to their template arguments
template<typename T>
class Vector {
public:
    using value_type = T;
    // ...
};

// In fact, every standard-library container provides value_type as the name for the type of its elements

template<typename C>
using Value_type = C::value_type; // the type of C’s elements
template<typename Container>
void algo(Container &c) {
    Vector<Value_type<Container> > vec; // keep results here
    // ...
}

// This Value_type is a simplified version of the standard library range_value_t

// The aliasing mechanism can be used to define a new template by binding some or all template arguments.
template<typename Key, typename Value>
class Map {
    // ...
};

template<typename Value>
using String_map = Map<string, Value>;
String_map<int> m; // m is a Map<string,int>F

// Compile-Time if

// Consider writing an operation that can be implemented using one of two functions slow_and_safe(T) or simple_and_fast(T)
// We can use a compile-time if:
template<typename T>
void update(T &target) {
    // ...
    if constexpr (is_trivially_copyable_v<T>)
        simple_and_fast(target); // for "plain old data"
    else
        slow_and_safe(target); // for more complex types
    // ...
}

template<typename T>
void bad(T arg) {
    if constexpr (!is_trivially_copyable_v<T>)
        try {
            // Oops, the if extends beyond this line
            g(arg);
            if constexpr (!is_trivially_copyable_v<T>);

        } catch (...) {
            /* ... */
        } // syntax error
}
