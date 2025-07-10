enum class Error_action { ignore, throwing, terminating, logging }; // error-handling alternatives

constexpr Error_action default_Error_action = Error_action::throwing; // a default

enum class Error_code { range_error, length_error }; // individual errors

string error_code_name[]{"range error", "length error"}; // names of individual errors

template<Error_action action = default_Error_action, class C>

constexpr void expect(C cond, Error_code x) // take "action" if the expected condition "cond" doesn’t hold
{
    if constexpr (action == Error_action::logging)
        if (!cond()) std::cerr << "expect() failure: " << int(x) << ' ' << error_code_name[int(x)] << '\n';
    if constexpr (action == Error_action::throwing)
        if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
        if (!cond()) terminate();
    // or no action
}

double &Vector::operator[](int i) {
    // call using lambda
    expect([i,this] { return 0 <= i && i < size(); }, Error_code::range_error);
    return elem[i];
}

// Works only in debug, if not a debug it will be ignored
void f(const char *p) {
    assert(p != nullptr); // p must not be the nullptr
    // ...
}

// Works on compile time
static_assert(4 <= sizeof(int), "integers are too small"); // check integer size

constexpr double C = 299792.458; // km/s
void f(double speed) {
    constexpr double local_max = 160.0 / (60 * 60); // 160 km/h == 160.0/(60*60) km/s
    static_assert(speed < C, "can't go that fast"); // error: speed must be a constant
    static_assert(local_max < C, "can't go that fast"); // OK
    // ...
}

// noexcept will terminate app if there is a exception
void user(int sz) noexcept {
    Vector v(sz);
    iota(&v[0], &v[sz], 1); // fill v with 1,2,3,4... (see §17.3)
    // ...
}
