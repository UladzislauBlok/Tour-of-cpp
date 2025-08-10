// An array, defined in <array>, is a fixed-size sequence of elements of a given type where the number
// of elements is specified at compile time
// array can and must be initialized by an initializer list:
array<int,3> a1 = {1,2,3};

// The element count is not optional, the element count must be a constant expression, the number
// of elements must be positive, and the element type must be explicitly stated:
void f(int n)
{
    array<int> a0 = {1,2,3}; // error size not specified
    array<string,n> a1 = {"John's", "Queens' "}; // error: size not a constant expression
    array<string,0> a2; // error: size must be positive
    array<2> a3 = {"John's", "Queens' "}; // error: element type not stated
    // ...
}
// When necessary, an array can be explicitly passed to a C-style function that expects a pointer.
void f(int* p, int sz); // C-style interface
void g()
{
    array<int,10> a;
    f(a,a.size()); // error: no conversion
    f(a.data(),a.size()); // C-style use
    auto p = find(a,777); // C++/STL-style use (a range is passed)
    // ...
}

// Main reason to prefer array is that it saves me from surprising and nasty conversions to pointers.
// Consider an example involving a class hierarchy:
void h()
{
    Circle a1[10];
    array<Circle,10> a2;
    // ...
    Shape* p1 = a1; // OK: disaster waiting to happen
    Shape* p2 = a2; // error: no conversion of array<Circle,10> to Shape* (Good!)
    p1[3].draw(); // disaster
}
// The ‘disaster’ comment assumes that sizeof(Shape)<sizeof(Circle), so subscripting a Circle[] through
// a Shape∗ gives a wrong offset. All standard containers provide this advantage over built-in arrays.

// ----

// bitset
// Class bitset<N> is providing operations on a sequence of N bits [0:N), where N is known at compile time
// For smaller sets, bitset is usually optimized
// A bitset can be initialized with an integer or a string:
bitset<9> bs1 {"110001111"};
bitset<9> bs2 {0b1'1000'1111}; // binary literal using digit separators (§1.4)
// The usual bitwise operators and the left- and right-shift operators (<< and >>) can be applied:
bitset<9> bs3 = ~bs1; // complement: bs3=="001110000"
bitset<9> bs4 = bs1&bs3; // all zeros
bitset<9> bs5 = bs1<<2; // shift left: bs5 = "000111100"
// The shift operators (here, <<) ‘shift in’ zeros.
// The operations to_ullong() and to_string() provide the inverse operations to the constructors. For
// example, we could write out the binary representation of an int:
void binary(int i)
{
    bitset<8*sizeof(int)> b = i; // assume 8-bit byte (see also §17.7)
    cout << b.to_string() << '\n'; // write out the bits of i
}
// This prints the bits represented as 1s and 0s from left to right, with the most significant bit leftmost,
// so that argument 123 would give the output
// 00000000000000000000000001111011
// A bitset offers many functions for using and manipulating sets of bits, such as all(), any(), none(), count(), flip().

// ----

// pair
// It is fairly common for a function to return two values
struct My_res {
    Entry* ptr;
    Error_code err;
};
My_res complex_search(vector<Entry>& v, const string& s)
{
    Entry* found = nullptr;
    Error_code err = Error_code::found;
    // ... search for s in v ...
    return {found,err};
}
void user(const string& s)
{
    My_res r = complex_search(entry_table,s); // search entry_table
    if (r.err != Error_code::good) {
        // ... handle error ...
    }
    // ... use r.ptr ....
}

// Using pair:
pair<Entry*,Error_code> complex_search(vector<Entry>& v, const string& s)
{
    Entry* found = nullptr;
    Error_code err = Error_code::found;
    // ... search for s in v ...
    return {found,err};
}
void user(const string& s)
{
    auto r = complex_search(entry_table,s); // search entry_table
    if (r.second != Error_code::good) {
        // ... handle error ...
    }
    // ... use r.first ....
}
// The members of pair are named first and second.
void user(const string& s)
{
    auto [ptr,success] = complex_search(entry_table,s); // search entry_table
    if (success != Error_code::good) {
        // ... handle error ...
    }
// ... use r.ptr ....
}

// The standard-library pair (from <utility>) is quite frequently used for ‘pair of values’ use cases in the standard library and elsewhere
// Algorithm equal_range returns a pair of iterators specifying a subsequence meeting a predicate:
template<typename Forward_iterator, typename T, typename Compare>
pair<Forward_iterator,Forward_iterator>
equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);

auto less = [](const Record& r1, const Record& r2) { return r1.name<r2.name;}; // compare names
void f(const vector<Record>& v) // assume that v is sorted on its "name" field
{
    auto [first,last] = equal_range(v.begin(),v.end(),Record{"Reg"},less);
    for (auto p = first; p!=last; ++p) // print all equal records
        cout << *p; // assume that << is defined for Record
}

// A pair provides operators, such as =, ==, and <, if its elements do. Type deduction makes it easy to
// create a pair without explicitly mentioning its type.
void f(vector<string>& v)
{
    pair p1 {v.begin(),2}; // one way
    auto p2 = make_pair(v.begin(),2); // another way
    // ...
}
// Both p1 and p2 are of type pair<vector<string>::iterator,int>.

// ----

// tuple
// he standard library provides tuple as a generalization of pair with zero or more elements:
tuple t0 {}; // empty
tuple<string,int,double> t1 {"Shark",123,3.14}; // the type is explicitly specified
auto t2 = make_tuple(string{"Herring"},10,1.23); // the type is deduced to tuple<string,int,double>
tuple t3 {"Cod"s,20,9.99}; // the type is deduced to tuple<string,int,double>

// Members of a tuple are accessed through a get function template.
string fish = get<0>(t1); // get the first element: "Shark"
int count = get<1>(t1); // get the second element: 123
double price = get<2>(t1); // get the third element: 3.14

// The function get is a template function taking the index as a template value argument
// Accessing members of a tuple by their index is general, ugly, and somewhat error-prone.
// Fortunately, an element of a tuple with a unique type in that tuple can be ‘named’ by its type:
auto fish = get<string>(t1); // get the string: "Shark"
auto count = get<int>(t1); // get the int: 123
auto price = get<double>(t1); // get the double: 3.14
// We can use get<> for writing also:
get<string>(t1) = "Tuna"; // write to the string
get<int>(t1) = 7; // write to the int
get<double>(t1) = 312; // write to the double

// Most uses of tuples are hidden in implementations of higher-level constructs.
// For example, we could access the members of t1 using structured binding:
void f() {
    auto [fish, count, price] = t1;
    cout << fish << ' ' << count << ' ' << price << '\n'; // read
    fish = "Sea Bass"; // write
}
// Typically, such binding and its underlying use of a tuple is used for a function call:
void f1() {
    auto [fish, count, price] = todays_catch();
    cout << fish << ' ' << count << ' ' << price << '\n';
}
// The real strength of tuple is when you have to store or pass around an unknown number of elements of unknown types as an object.
// Explicitly, iterating over the elements of a tuple is a bit messy, requiring recursion and compiletime evaluation of the function body:
template <size_t N = 0, typename... Ts>
constexpr void print(tuple<Ts...> tup)
{
    if constexpr (N<sizeof...(Ts)) { // not yet at the end?
        cout << get<N>(tup) << ' '; // print the Nth element
        print<N+1>(tup); // print the next element
    }
}
// Here, sizeof...(Ts) gives the number of elements in Ts

// Like pair, tuple provides operators, such as =, ==, and <, if its elements do.
// There are also conversions between a pair and a tuple with two members

