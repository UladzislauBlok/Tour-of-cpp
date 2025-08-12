// A type function is a function that is evaluated at compile time given a type as its argument or returning a type.

// For numerical types, numeric_limits from <limits> presents a variety of useful information
constexpr float min = numeric_limits<float>::min(); // smallest positive float

// Similarly, object sizes can be found by the built-in sizeof operator.
constexpr int szi = sizeof(int); // the number of bytes in an in

// In <type_traits>, the standard library provides many functions for inquiring about properties of types
bool b = is_arithmetic_v<X>; // true if X is one of the (built-in) arithmetic types
using Res = invoke_result_t<decltype(f)>; // Res is int if f is a function that returns an int
// The decltype(f) is a call of the built-in type function decltype() returning the declared type of its argument; here f.

// Some type functions create new types based on inputs.
typename<typename T>
using Store = conditional_t(sizeof(T)<max, On_stack<T>, On_heap<T>);

// Concepts are type functions. When used in expressions, they are specifically type predicates.
template<typename F, typename... Args>
auto call(F f, Args... a, Allocator alloc)
{
    if constexpr (invocable<F,alloc,Args...>) // needs an allocator?
        return f(f,alloc,a...);
    else
        return f(f,a...);
}

// One traditional use of these predicates is to constrain template arguments.
template<typename Scalar>
class complex {
    Scalar re, im;
public:
    static_assert(is_arithmetic_v<Scalar>, "Sorry, I support only complex of arithmetic types");
    // ...
};

// However, that – like other traditional uses – is easier and more elegantly done using concepts:
template<Arithmetic Scalar>
class complex {
    Scalar re, im;
public:
    // ...
};

// Consider defining a ‘smart pointer’:
template<typename T>
class Smart_pointer {
    // ...
    T& operator*() const;
    T* operator->() const; // -> should work if and only if T is a class
};

// The -> should be defined if and only if T is a class type. For example, Smart_pointer<vector<T>>
// should have ->, but Smart_pointer<int> should not.
// We cannot use a compile-time if because we are not inside a function.
template<typename T>
class Smart_pointer {
    // ...
    T& operator*() const;
    T* operator->() const requires is_class v<T>; // -> is defined if and only if T is a class
};

// Of these, enable_if is probably the most common in pre-concepts code.
// For example, the conditionally enabled -> for a smart pointer is traditionally implemented something like this:
template<typename T>
class Smart_pointer {
    // ...
    T& operator*();
    enable_if<is_class v<T>,T&> operator->(); // -> is defined if and only if T is a class
};

