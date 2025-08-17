// The simplest ‘event’ is simply time passing
void f() {
    using namespace chrono; // see §16.2.1
    auto t0 = high_resolution_clock::now();
    this_thread::sleep_for(milliseconds{20});
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed\n";
}

// A condition_variable is a mechanism allowing one thread to wait for another.
// In particular, it allows a thread to wait for some condition

class Message { // object to be communicated
    // ...
};
queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex; // for synchronizing access to mcond

// The types queue, condition_variable, and mutex are provided by the standard library.
// The consumer() reads and processes Messages:
void consumer()
{
    while(true) {
        unique_lock lck {mmutex}; // acquire mmutex
        mcond.wait(lck,[] { return !mqueue.empty(); }); // release mmutex and wait;
        // re-acquire mmutex upon wakeup
        // don’t wake up unless mqueue is non-empty
        auto m = mqueue.front(); // get the message
        mqueue.pop();
        lck.unlock(); // release mmutex
        // ... process m ...
    }
}

// The corresponding producer looks like this:
void producer()
{
    while(true) {
        Message m;
        // ... fill the message ...
        scoped_lock lck {mmutex}; // protect operations
        mqueue.push(m);
        mcond.notify_one(); // notify
    } // release mmutex (at end of scope)
}

