// An iostream has a state that we can examine to determine whether an operation succeeded.
// The most common use is to read a sequence of values:
vector<int> read_ints(istream& is)
{
    vector<int> res;
    for (int i; is>>i; )
        res.push_back(i);
    return res;
}
// This reads from is until something that is not an integer is encountered
// What is happening here is that the operation is>>i returns a reference to 'is',
// and testing an iostream yields true if the stream is ready for another operation.

// In general, the I/O state holds all the information needed to read or write,
// such as formatting information, error state (e.g., has end-of-input been reached?), and what kind of buffering is used.

vector<int> read_ints(istream& is, const string& terminator)
{
    vector<int> res;
    for (int i; is >> i; )
        res.push_back(i);
    if (is.eof()) // fine: end of file
        return res;
    if (is.fail()) { // we failed to read an int; was it the terminator?
        is.clear(); // reset the state to good()
        string s;
        if (is>>s && s==terminator)
            return res;
        is.setstate(ios_base::failbit); // add fail() to is’s state
    }
    return res;
}
auto v = read_ints(cin,"stop");