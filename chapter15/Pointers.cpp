// The general notion of a pointer is something that allows us to refer to an object and to access it
// according to its type. A built-in pointer, such as int∗, is an example but there are many more.

// In <memory>, the standard library provides two ‘smart pointers’ to help manage objects on the free store:
// • unique_ptr represents unique ownership (its destructor destroys its object)
// • shared_ptr represents shared ownership (the last shared pointer’s destructor destroys the object)
// The most basic use of these ‘smart pointers’ is to prevent memory leaks caused by careless programming.
void f(int i, int j) // X* vs. unique_ptr<X>
{
    X* p = new X; // allocate a new X
    unique_ptr<X> sp {new X}; // allocate a new X and give its pointer to unique_ptr
    // ...
    if (i<99) throw Z{}; // may throw an exception
    if (j<77) return; // may return "early"
    // ... use p and sp ..
    delete p; // destroy *p
}
// Here, we ‘forgot’ to delete p if i<99 or if j<77.

// unique_ptr is a lightweight mechanism with no space or time overhead compared to correct use of a built-in pointer.
// Its further uses include passing free-store allocated objects in and out of functions:
unique_ptr<X> make_X(int i) // make an X and immediately give it to a unique_ptr
{
    // ... check i, etc. ...
    return unique_ptr<X>{new X{i}};
}

// The shared_ptr is similar to unique_ptr except that shared_ptrs are copied rather than moved.
// The shared_ptrs for an object share ownership of an object; that object is destroyed when the last of its shared_ptrs is destroyed.
void f(shared_ptr<fstream>);
void g(shared_ptr<fstream>);

void user(const string& name, ios_base::openmode mode)
{
    shared_ptr<fstream> fp {new fstream(name,mode)};
    if (!*fp) // make sure the file was properly opened
        throw No_file{};
    f(fp);
    g(fp);
    // ...
}

// <memory> provides functions for constructing an object and returning an appropriate smart pointer, make_shared() and make_unique().
struct S {
    int i;
    string s;
    double d;
    // ...
};
auto p1 = make_shared<S>(1,"Ankh Morpork",4.65); // p1 is a shared_ptr<S>
auto p2 = make_unique<S>(2,"Oz",7.62); // p2 is a unique_ptr<S>

