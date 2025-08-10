// variant<T...> One of a specified set of alternatives (in <variant>)
variant<string,Error_code> compose_message(istream& s)
{
    string mess;
    // ... read from s and compose message ...
    if (no_problems)
        return mess; // return a string
    else
        return Error_code{some_problem}; // return an Error_code
}
// When you assign or initialize a variant with a value, it remembers the type of that value.
// Later, we can inquire what type the variant holds and extract the value.
void f() {
    auto m = compose_message(cin);
    if (holds_alternative<string>(m)) {
        cout << get<string>(m);
    }
    else {
        auto err = get<Error_code>(m);
        // ... handle error ...
    }
}

// Pattern of checking alternatives to decide on the appropriate action is so common
// and relatively inefficient that it deserves direct support:
void check(Node* p)
{
    visit(overloaded {
    [](Expression& e) { /* ... */ },
    [](Statement& s) { /* ... */ },
    // ... Declaration and Type ...
    }, *p);
}

// ----

// optional
// An optional<A> can be seen as a special kind of variant (like a variant<A,nothing>)
// or as a generalization of the idea of an A∗ either pointing to an object or being nullptr.
// An optional can be useful for functions that may or may not return an object:
optional<string> compose_message(istream& s)
{
    string mess;
    // ... read from s and compose message ...
    if (no_problems)
        return mess;
    return {}; // the empty optional
}

// Given that, we can write
void f1() {
    if (auto m = compose_message(cin))
        cout << *m; // note the dereference (*)
    else {
        // ... handle error ...
    }
}

// Note the curious use of ∗. An optional is treated as a pointer to its object rather than the object itself.
// The optional equivalent to nullptr is the empty object, {}.
int sum(optional<int> a, optional<int> b)
{
    int res = 0;
    if (a) res+=*a;
    if (b) res+=*b;
    return res;
}
int x = sum(17,19); // 36
int y = sum(17,{}); // 17
int z = sum({},{}); // 0


// If we try to access an optional that does not hold a value, the result is undefined; an exception is not
// thrown. Thus, optional is not guaranteed type safe. Don’t try:
int sum2(optional<int> a, optional<int> b)
{
    return *a+*b; // asking for trouble
}

// ----

// any
// An any can hold an arbitrary type and know which type (if any) it holds. It is basically an unconstrained version of variant:
any compose_message(istream& s)
{
    string mess;
    // ... read from s and compose message ...
    if (no_problems)
        return mess; // return a string
    else
        return error_number; // return an int
}

// When you assign or initialize an any with a value, it remembers the type of that value.
// Later, we can extract the value held by the any by asserting the value’s expected type. For example:
void f2() {
    auto m = compose_message(cin);
    string& s = any_cast<string&>(m);
    cout << s;
}
// If we try to access an any holding a different type than the expected one, bad_any_access is thrown.