struct Entry {
    string name;
    int number;
};

// We can define a simple output operator to write an Entry using a {"name",number} format similar to
// the one we use for initialization in code:
ostream &operator<<(ostream &os, const Entry &e) {
    return os << "{\"" << e.name << "\", " << e.number << "}";
}

istream &operator>>(istream &is, Entry &e)
// read { "name" , number } pair. Note: formatted with { " " , and }
{
    char c, c2;
    if (is >> c && c == '{' && is >> c2 && c2 == '"') {
        // start with a { followed by a "
        string name; // the default value of a string is the empty string: ""
        while (is.get(c) && c != '"') // anything before a " is part of the name
            name += c;
        if (is >> c && c == ',') {
            int number = 0;
            if (is >> number >> c && c == '}') {
                // read the number and a }
                e = {name, number}; // assign to the entry
                return is;
            }
        }
    }
    is.setstate(ios_base::failbit); // register the failure in the stream
    return is;
}

// An input operation returns a reference to its istream that can be used to test if the operation succeeded

// We can read such a pair of values from input into an Entry like this:
void f() {
    for (Entry ee; cin >> ee;) // read from cin into ee
        cout << ee << '\n'; // write ee to cout
}
// The output is:
// { "John Marwood Cleese", 123456 }
// {"Michael Edward Palin", 987654}
