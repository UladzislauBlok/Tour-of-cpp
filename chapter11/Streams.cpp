// The standard library directly supports
// • Standard streams: streams attached to the system’s standard I/O streams
// • File streams: streams attached to files
// • String streams: streams attached to strings
// • Memory streams: stream attached to specific areas of memory
// • Synchronized streams: streams that can be used from multiple threads without data races

// Streams cannot be copied; always pass them by reference.
// ostream is basic_ostream<char>. For each such stream, the standard library also provides a version for wchar_ts.
// wostream is basic_ostream<wchar_t>. The wide character streams can be used for unicode characters

// The standard streams are
// • cout for ‘ordinary output’
// • cerr for unbuffered ‘error output’
// • clog for buffered ‘logging output’
// • cin for standard input

// File Streams
// In <fstream>, the standard library provides streams to and from a file:
// • ifstreams for reading from a file
// • ofstreams for writing to a file
// • fstreams for reading from and writing to a file
// For example:

void f() {
    ofstream ofs {"target"}; // ‘o’ for ‘output’
    if (!ofs)
        error("couldn't open 'target' for writing");
}

// Testing that a file stream has been properly opened is usually done by checking its state.
void f1() {
    ifstream ifs {"source"}; // ‘‘i’’ for ‘‘input’’
    if (!ifs)
        error("couldn't open 'source' for reading");
}


// String streams
// In <sstream>, the standard library provides streams to and from a string:
// • istringstreams for reading from a string
// • ostringstreams for writing to a string
// • stringstreams for reading from and writing to a string

void test()
{
    ostringstream oss;
    oss << "{temperature," << scientific << 123.4567890 << "}";
    cout << oss.view() << '\n';
}
// The contents of an ostringstream can be read using str() (a string copy of the contents)
// or view() (a string_view of the contents).

// A stringstream can be used for both reading and writing
template<typename Target =string, typename Source =string>
Target to(Source arg) // convert Source to Target
{
    stringstream buf;
    Target result;
    if (!(buf << arg) // write arg into stream
    || !(buf >> result) // read result from stream
    || !(buf >> std::ws).eof()) // is anything left in stream?
        throw runtime_error{"to<>() failed"};
    return result;
}

void f2() {
    auto x1 = to<string,double>(1.2); // very explicit (and verbose)
    auto x2 = to<string>(1.2); // Source is deduced to double
    auto x3 = to<>(1.2); // Target is defaulted to string; Source is deduced to double
    auto x4 = to(1.2); // the <> is redundant. Target is defaulted to string; Source is deduced to double
}

// Memory Streams
// An ospanstream behaves like an ostringstream and is initialized like it except that the
// ospanstream takes a span rather than a string as an argument. For example:
void user(int arg)
{
    array<char,128> buf;
    ospanstream ss(buf);
    ss << "write " << arg << " to memory\n";
    // ...
}
// Attempts overflow the target buffer sets the string state to failure
// Similarly, an ispanstream is like an istringstream.

// Synchronized Streams
// In a multi-threaded system, I/O becomes an unreliable mess unless either
// • Only one thread uses the stream.
// • Access to a stream is synchronized so that only one thread at a time gains access.
// An osyncstream guarantees that a sequence of output operations will complete and their results will
// be as expected in the output buffer even if some other thread tries to write. For example:
void unsafe(int x, string& s)
{
    cout << x;
    cout << s;
}
// A different thread may introduce a data race (§18.2) and lead to surprising output.
// An osyncstream can be used to avoid that
void safer(int x, string& s)
{
    osyncstream oss(cout);
    oss << x;
    oss << s;
}