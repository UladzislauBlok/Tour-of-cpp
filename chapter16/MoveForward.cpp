// If you want a unique_ptr elsewhere, you must move it.
void f1()
{
    auto p = make_unique<int>(2);
    auto q = p; // error: we can’t copy a unique_ptr
    auto q = move(p); // p now holds nullptr
    // ...
}

// std::move() doesn’t move anything, it casts its argument to an rvalue reference
template <typename T>
void swap(T& a, T& b)
{
    T tmp {move(a)}; // the T constructor sees an rvalue and moves
    a = move(b); // the T assignment sees an rvalue and moves
    b = move(tmp); // the T assignment sees an rvalue and moves
}

// As for other casts, there are tempting, but dangerous, uses of std::move()
string s1 = "Hello";
string s2 = "World";
vector<string> v;
v.push_back(s1); // use a "const string&" argument; push_back() will copy
v.push_back(move(s2)); // use a move constructor
v.emplace_back(s1); // an alternative; place a copy of s1 in a new end position of v

// If we use s2
again, we have a problem:
cout << s1[2]; // write ’l’
cout << s2[2]; // crash?

// The compiler knows that a return value is not used again in a function, so using an explicit
// std::move(), e.g., return std::move(x), is redundant and can even inhibit optimizations.


// Forwarding arguments is an important use case that requires moves
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>{new T{std::forward<Args>(args)...}}; // forward each argument
}
// The standard-library forward() differs from the simpler std::move() by correctly handling subtleties to do with lvalue and rvalue
// Use std::forward() exclusively for forwarding and don’t forward() something twice; once you have forwarded an object, it’s not yours to use anymore