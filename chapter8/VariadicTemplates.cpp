// A template can be defined to accept an arbitrary number of arguments of arbitrary types.
// Such a template is called a variadic template.
// Consider a simple function to write out values of any type that has a << operator:
void user() {
    print("first: ", 1, 2.2, "hello\n"s); // first: 1 2.2 hello
    print("\nsecond: ", 0.2, 'c', "yuck!"s, 0, 1, 2, '\n'); // second: 0.2 c yuck! 0 1 2
}

template<typename T>
concept Printable = requires(T t) { std::cout << t; } // just one operation!
void print() {
    // what we do for no arguments: nothing
}
template<Printable T, Printable... Tail>
void print(T head, Tail... tail) {
    cout << head << ' '; // first, what we do for the head
    print(tail...); // then, what we do for the tail
}
// The Printable... indicates that Tail is a sequence of types.
// The Tail... indicates that tail is a sequence of values of the types in Tail

// If we don’t want to allow the zero-argument case, we can eliminate that print() using a compile-time if:
template<Printable T, Printable... Tail>
void print(T head, Tail... tail) {
    cout << head << ' ';
    if constexpr(sizeof...(tail)> 0)
        print(tail...);
}

// The strength of variadic templates is that they can accept any arguments you care to give them.
// Weaknesses include
// • The recursive implementations can be tricky to get right.
// • The type checking of the interface is a possibly elaborate template program.
// • The type checking code is ad hoc, rather than defined in the standard.
// • The recursive implementations can be surprisingly expensive in compile time and compiler memory requirements.

// Fold Expressions
template<Number... T>
int sum(T... v) {
    return (v + ... + 0); // add all elements of v starting with 0
}
// This sum() can take any number of arguments of any types:
int x = sum(1, 2, 3, 4, 5); // x becomes 15
int y = sum('a', 2.4, x); // y becomes 114 (2.4 is truncated and the value of ’a’ is 97)
// The body of sum uses a fold expression:
return (v + ... + 0); // add all elements of v to 0
// That is, starting from the right where the 0 is. It is called a right fold.

// Alternatively, we could have used a left fold:
template<Number... T>
int sum2(T... v){
    return (0 + ... + v); // add all elements of v to 0
}
// Now, the first element to be added is the ‘leftmost’

template<Printable ...T>
void print(T&&... args) {
    (std::cout << ... << args) << '\n'; // print all arguments
}
print("Hello!"s,' ',"World ",2017); // (((((std::cout << "Hello!"s) << ’ ’) << "World ") << 2017) << ’\n’);

// Passing arguments unchanged through an interface is an important use of variadic templates.
// Consider a notion of a network input channel for which the actual method of moving values is a parameter.
// Different transport mechanisms have different sets of constructor parameters:
template<concepts::InputTransport Transport>
class InputChannel {
public:
    // ...
    InputChannel(Transport::Args&&... transportArgs)
    : _transport(std::forward<TransportArgs>(transportArgs)...)
    {}
    // ...
    Transport _transport;
};
// The standard-library function forward() (§16.6) is used to move the arguments unchanged from the
// InputChannel constructor to the Transport constructor.