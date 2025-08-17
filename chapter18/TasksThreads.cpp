// We call a computation that can potentially be executed concurrently with other computations a task.
// A thread is the system-level representation of a task in a program
void f(); // function
struct F { // function object
    void operator()(); // F’s call operator (§7.3.2)
};
void user()
{
    thread t1 {f}; // f() executes in separate thread
    thread t2 {F{}}; // F{}() executes in separate thread
    t1.join(); // wait for t1
    t2.join(); // wait for t2
}
// The join() ensure that we don’t exit user() until the threads have completed.

// jthread, which is a ‘joining thread’ follows RAII by having its destructor join():
void user()
{
    jthread t1 {f}; // f() executes in separate thread
    jthread t2 {F{}}; // F{}() executes in separate thread
}

// Typically, a task needs data to work upon. We can easily pass data (or pointers or references to the data) as arguments.
void f(vector<double>& v); // function: do something with v
struct F { // function object: do something with v
    vector<double>& v;
    F(vector<double>& vv) :v{vv} { }
    void operator()(); // application operator; §7.3.2
};
int main()
{
    vector<double> some_vec {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> vec2 {10, 11, 12, 13, 14};
    jthread t1 {f,ref(some_vec)}; // f(some_vec) executes in a separate thread
    jthread t2 {F{vec2}}; // F(vec2)() executes in a separate thread
}

// Returning Results
void f(const vector<double>& v, double* res); // take input from v; place result in *res
class F {
public:
    F(const vector<double>& vv, double* p) :v{vv}, res{p} { }
    void operator()(); // place result in *res
private:
    const vector<double>& v; // source of input
    double* res; // target for output
};
double g(const vector<double>&); // use return value
void user(vector<double>& vec1, vector<double> vec2, vector<double> vec3)
{
    double res1;
    double res2;
    double res3;
    thread t1 {f,cref(vec1),&res1}; // f(vec1,&res1) executes in a separate thread
    thread t2 {F{vec2,&res2}}; // F{vec2,&res2}() executes in a separate thread
    thread t3 { [&](){ res3 = g(vec3); } }; // capture local variables by reference
    t1.join(); // join before using results
    t2.join();
    t3.join();
    cout << res1 << ' ' << res2 << ' ' << res3 << '\n';
}
// Here, cref(vec1) passes a const reference to vec1 as an argument to t1.