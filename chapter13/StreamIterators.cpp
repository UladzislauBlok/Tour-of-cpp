// To make an ostream_iterator, we need to specify which stream will be used and the type of objects written to it.
ostream_iterator<string> oo {cout}; // write strings to cout

// The effect of assigning to ∗oo is to write the assigned value to cout.
int main() {
    *oo = "Hello, "; // meaning cout<<"Hello, "
    ++oo;
    *oo = "world!\n"; // meaning cout<<"world!\n"
}

// That way, we can use algorithms on streams.
void f() {
    vector<string> v{ "Hello", ", ", "World!\n" };
    copy(v, oo);
}

// We can write a simple program to read a file, sort the words read, eliminate duplicates, and write the result to another file:
int main() {
    string from, to;
    cin >> from >> to; // get source and target file names
    ifstream is {from}; // input stream for file "from"
    istream_iterator<string> ii {is}; // input iterator for stream
    istream_iterator<string> eos {}; // input sentinel
    ofstream os {to}; // output stream for file "to"
    ostream_iterator<string> oo {os,"\n"}; // output iterator for stream plus a separator
    vector<string> b {ii,eos}; // b is a vector initialized from input
    sort(b); // sort the buffer
    unique_copy(b,oo); // copy the buffer to output, discard replicated values
    return !is.eof() || !os; // return error state
}

// Please remember that to use both a traditional iterator version of a standard-library algorithm and its ranges counterpart,
// we need to either explicitly qualify the call of the range version or use a using-declaration:
void f1() {
    copy(v, oo); // potentially ambiguous
    ranges::copy(v, oo); // OK
    using ranges::copy(v, oo); // copy(v, oo) OK from here on
    copy(v, oo); // OK
}

int main() {
    string from, to;
    cin >> from >> to; // get source and target file names
    ifstream is {from}; // input stream for file "from"
    ofstream os {to}; // output stream for file "to"
    set<string> b {istream_iterator<string>{is},istream_iterator<string>{}}; // read input
    copy(b,ostream_iterator<string>{os,"\n"}); // copy to output
    return !is.eof() || !os; // return error state
}

