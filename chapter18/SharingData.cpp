// A mutex, a ‘mutual exclusion object,’ is a key element of general sharing of data between threads.
// A thread acquires a mutex using a lock() operation:
mutex m; // controlling mutex
int sh; // shared data
void f()
{
    scoped_lock lck {m}; // acquire mutex
    sh += 7; // manipulate shared data
} // release mutex implicitly
// Use of resource handles, such as scoped_lock and unique_lock is simpler and far safer than explicitly locking and unlocking mutexes.

// The scoped_lock helps by enabling us to acquire several locks simultaneously:
void f()
{
    scoped_lock lck {mutex1,mutex2,mutex3}; // acquire all three locks
    // ... manipulate shared data ...
} // implicitly release all mutexes

//Read/write locks:
shared_mutex mx; // a mutex that can be shared
void reader()
{
    shared_lock lck {mx}; // willing to share access with other readers
    // ... read ...
}
void writer()
{
    unique_lock lck {mx}; // needs exclusive (unique) access
    // ... write ...
}

// an atomic variable:
void f() {
    mutex mut;
    atomic<bool> init_x; // initially false.
    X x; // variable that requires nontrivial initialization
    if (!init_x) {
        lock_guard lck {mut};
        if (!init_x) {
            // ... do nontrivial initialization of x ...
            init_x = true;
        }
    }
    // ... use x ...
}