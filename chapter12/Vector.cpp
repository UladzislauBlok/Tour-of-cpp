// A typical implementation of vector will consist of a handle holding pointers to the first element,
// one-past-the-last element, and one-past-the-last allocated space

// We can initialize a vector with a set of values of its element type:
void f() {
    vector<Entry> phone_book = {
        {"David Hume", 123456},
        {"Karl Popper", 234567},
        {"Bertrand Arthur William Russell", 345678}
    };
}

// Elements can be accessed through subscripting
void print_book(const vector<Entry> &book) {
    for (int i = 0; i != book.size(); ++i)
        cout << book[i] << '\n';
}

// The elements of a vector constitute a range, so we can use a range-for loop:
void print_book(const vector<Entry> &book) {
    for (const auto &x: book)
        cout << x << '\n';
}

// When we define a vector, we give it an initial size (initial number of elements):
void f1() {
    vector<int> v1 = {1, 2, 3, 4}; // size is 4
    vector<string> v2; // size is 0
    vector<Shape*> v3(23); // size is 23; initial element value: nullptr
    vector<double> v4(32, 9.9); // size is 32; initial element value: 9.9
}

// One of the most useful operations on a vector is push_back(),
// which adds a new element at the end of a vector, increasing its size by one
void input() {
    for (Entry e; cin>>e; )
        phone_book.push_back(e);
}

// The standard-library vector is implemented so that growing a vector by repeated push_back()s is efficient
template<typename T>
class Vector {
    allocator<T> alloc; // standard-library allocator of space for Ts
    T* elem; // pointer to first element
    T* space; // pointer to first unused (and uninitialized) slot
    T* last; // pointer to last slot
public:
    // ...
    int size() const { return space-elem; } // number of elements
    int capacity() const { return last-elem; } // number of slots available for elements
    // ...
    void reserve(int newsz); // increase capacity() to newsz
    // ...
    void push_back(const T& t); // copy t into Vector
    void push_back(T&& t); // move t into Vector
};

template<typename T>
void Vector<T>::push_back(const T& t) {
    if (capacity()<=size()) // make sure we have space for t
        reserve(size()==0?8:2*size()); // double the capacity
    construct_at(space,t); // initialize *space to t ("place t at space")
    ++space;
}

// If you have a class hierarchy that relies on virtual functions to get polymorphic behavior,
// do not store objects directly in a container.
void f2() {
    vector<Shape> vs; // No, don’t - there is no room for a Circle or a Smiley (§5.5)
    vector<Shape*> vps; // better, but see §5.5.3 (don’t leak)
    vector<unique_ptr<Shape>> vups; // OK
}

// The standard-library vector does not guarantee range checking.
void silly(vector<Entry>& book) {
    int i = book[book.size()].number; // book.size() is out of range
    // ...
}
// That initialization is likely to place some random value in i rather than giving an error.

// Simple range-checking adaptation of vector:
template<typename T>
struct Vec : std::vector<T> {
    using vector<T>::vector; // use the constructors from vector (under the name Vec)
    T& operator[](int i) { return vector<T>::at(i); } // range check
    const T& operator[](int i) const { return vector<T>::at(i); } // range check const objects;
    auto begin() { return Checked_iter<vector<T>>{*this}; }
    auto end() { return Checked_iter<vector<T>>{*this, vector<T>::end()}; }
};

// For Vec, an out-of-range access will throw an exception that the user can catch.
void checked(Vec<Entry>& book) {
    try {
        book[book.size()] = {"Joe",999999}; // will throw an exception
        // ...
    }
    catch (out_of_range&) {
        cerr << "range error\n";
    }
}

