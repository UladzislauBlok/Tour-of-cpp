#include <iostream>

// In addition to type arguments, a template can take value arguments.
template<typename T, int N>
struct Buffer {
    constexpr int size() { return N; }
    T elem[N];
    // ...
};

// Value arguments are useful in many contexts. For example, Buffer allows us to create arbitrarily
// sized buffers with no use of the free store (dynamic memory):
Buffer<char, 1024> glob; // global buffer of characters (statically allocated)
void fct() {
    Buffer<int, 10> buf; // local buffer of integers (on the stack)
    // ...
}

// A string literal cannot yet be a template value argument.
// We can use an array holding the characters of a string:
template<char* s>
void outs() { std::cout << s; }

char arr[] = "Weird workaround!";

void use() {
    //outs<"straightforward use">(); error (for now)
    outs<arr>(); // writes: Weird workaround!
}
