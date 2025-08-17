// A coroutine is a function that maintains its state between calls. In that, it’s a bit like a function
// object, but the saving and restoring of its state between calls are implicit and complete

generator<long long> fib() // generate Fibonacci numbers
{
    long long a = 0;
    long long b = 1;
    while (a<b) {
        auto next = a+b;
        co_yield next; // save state, return value, and wait
        a = b;
        b = next;
    }
    co_return 0; // a fib too far
}

void user(int max)
{
    for (int i=0; i++<max;)
        cout << fib() << ' ';
}
// This generates
// 1 2 3 5 8 13 ...

// Cooperative Multitasking
// The keys to such designs are
// • Many different coroutines that maintain their state between calls.
// • A form of polymorphism that allows us to keep lists of events containing different kinds of coroutines and invoke them independently of their types.
// • A scheduler that selects the next coroutine(s) to run from the list(s).
struct Event_base {
    virtual void operator()() = 0;
    virtual ˜Event_base() {}
};
template<class Act>
struct Event : Event_base {
    Event(const string n, Act a) : name{ n }, act{ move(a) } {}
    string name;
    Act act;
    void operator()() override { act(); }
};
// The co_yield returns a value and waits for the next call.
// The co_return returns a value and terminates the coroutine

// An Event simply stores an action and allows it to be called;

void test()
{
    vector<Event_base*> events = { // create a couple of Events holding coroutines
        new Event{ "integers ", sequencer(10) },
        new Event{ "chars ", char_seq('a') }
    };
    vector order {0, 1, 1, 0, 1, 0, 1, 0, 0}; // choose some order
    for (int x : order) // invoke coroutines in order
        (*events[x])();
    for (auto p : events) // clean up
        delete p;
}

task sequencer(int start, int step =1)
{
    auto value = start;
    while (true) {
        cout << "value: " << value << '\n'; // communicate a result
        co_yield 0; // sleep until someone resumes this coroutine
        value += step; // update state
    }
}

task char_seq(char start)
{
    auto value = start;
    while (true) {
        cout << "value: " << value << '\n'; // communicate result
        co_yield 0;
        ++value;
    }
}
// The ‘magic’ is in the return type task; it holds the state of the coroutine (in effect the function’s
// stack frame) between calls and determines the meaning of the co_yield