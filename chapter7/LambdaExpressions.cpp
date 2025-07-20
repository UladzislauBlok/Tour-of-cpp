// Lambda Expressions is a notation for implicitly generating function objects
void f(const Vector<int> &vec, const list<string> &lst, int x, const string &s) {
    cout << "number of values less than " << x
            << ": " << count(vec, [&](int a) { return a < x; })
            << '\n';
    cout << "number of values less than " << s
            << ": " << count(lst, [&](const string &a) { return a < s; })
            << '\n';
}

// The notation [&](int a){ return a<x; } is called a lambda expression
// The [&] is a capture list specifying that all local names used in the lambda body (such as x) will be accessed through references
// If we wanted to give the generated object a copy of x, we could have said so: [x].
// Capture nothing is [ ], capture all local names used by reference is [&], and capture all local names used by value is [=].
// For a lambda defined within a member function, [this] captures the current object by reference so that we can refer to class members.
// If we want a copy of the current object, we say [∗this].

// function that applies an operation to each object pointed to by the elements of a container of pointers:
template<typename C, typename Oper>
void for_each(C &c, Oper op) { // assume that C is a container of pointers
    for (auto &x: c)
        op(x); // pass op() a reference to each element pointed to
}

// This is a simplified version of the standard-library for_each algorithm

void user() {
    vector<unique_ptr<Shape> > v;
    while (cin)
        v.push_back(read_shape(cin));
    for_each(v, [](unique_ptr<Shape> &ps) { ps->draw(); }); // draw_all()
    for_each(v, [](unique_ptr<Shape> &ps) { ps->rotate(45); }); // rotate_all(45)
}

// I pass the unique_ptr<Shape>s to the lambdas by reference.
// That way for_each() doesn’t have to deal with lifetime issues.
// Like a function, a lambda can be generic.
template<class S>
void rotate_and_draw(vector<S>& v, int r) {
    for_each(v,[](auto& s){ s->rotate(r); s->draw(); });
}

// Auto means that a value of any type is accepted as an initializer (an argument is considered to initialize the formal parameter in a call).
// This makes a lambda with an auto parameter a template, a generic lambda.
// When needed, we can constrain the parameter with a concept

// Such code is often messy, deemed essential ‘‘for efficiency,’’ and a source of bugs
enum class Init_mode { zero, seq, cpy, patrn }; // initializer alternatives
void user(Init_mode m, int n, vector<int>& arg, Iterator p, Iterator q) {
    vector<int> v;
    // messy initialization code:
    switch (m) {
        case zero:
            v = vector<int>(n); // n elements initialized to 0
            break;
        case cpy:
            v = arg;
            break;
    };
    // ...
    if (m == seq)
        v.assign(p,q); // copy from sequence [p:q)
    // ...
}

// Instead, we could convert it to a lambda used as an initializer:
void user(Init_mode m, int n, vector<int>& arg, Iterator p, Iterator q) {
    vector<int> v = [&] {
        switch (m) {
            case zero: return vector<int>(n); // n elements initialized to 0
            case seq: return vector<int>{p,q}; // copy from sequence [p:q)
            case cpy: return arg;
        }
    }();
    // ...
}

// If we need to do some cleanup that is not associated with a single object, or with an
// object that does not have a destructor (e.g., because it is a type shared with a C program),
// we can define a function, finally()

void old_style(int n) {
    void* p = malloc(n*sizeof(int)); // C-style
    auto act = finally([&]{free(p);}); // call the lambda upon scope exit
    // ...
}

template <class F>
[[nodiscard]] auto finally(F f) {
    return Final_action{f};
}

// [[nodiscard]] to ensure that users do not forget to copy a generated Final_action into the scope for which its action is intended.
// The class Final_action that supplies the necessary destructor can look like this:
template <class F>
struct Final_action {
    explicit Final_action(F f) :act(f) {}
    ~Final_action() { act(); }
    F act;
};
// There is a finally() in the Core Guidelines Support Library (the GSL) and a proposal for a more
// elaborate scope_exit mechanism for the standard library.