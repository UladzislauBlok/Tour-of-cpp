// The string type provides a variety of useful string operations, such as concatenation
string compose(const string& name, const string& domain) {
    return name + '@' + domain;
}
auto addr = compose("dmr","bell-labs.com");

// In many applications, the most common form of concatenation is adding something to the end
// of a string. This is directly supported by the += operation. For example:
void m2(string& s1, string& s2) {
    s1 = s1 + '\n'; // append newline
    s2 += '\n'; // append newline
}

// A string is mutable. In addition to = and +=, subscripting (using [ ]) and substring operations are supported.
string name = "Niels Stroustrup";
void m3() {
    string s = name.substr(6,10); // s = "Stroustrup"
    name.replace(0,5,"nicholas"); // name becomes "nicholas Stroustrup"
    name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup"
}

// Naturally, strings can be compared against each other, against C-style strings, and against string literals.
string incantation;
void respond(const string& answer) {
    if (answer == incantation) {
        // ... perform magic ...
    }
    else if (answer == "yes") {
        // ...
    }
    // ...
}

// If you need a C-style string (a zero-terminated array of char), string offers read-only access to its contained characters (c_str() and data()).
void print(const string& s)
{
    printf("For people who like printf: %s\n",s.c_str()); // s.c_str() returns a pointer to s’ characters
    cout << "For people who like streams: " << s << '\n';
}

// A string literal is by definition a const char∗. To get a literal of type std::string use an s suffix.
auto cat = "Cat"s; // a std::string
auto dog = "Dog"; // a C-style string: a const char*
// To use the s suffix, you need to use the namespace std::literals::string_literals

// string is usually implemented using the short-string optimization.
// That is, short string values are kept in the string object itself and only longer strings are placed on free store.
string s1 {"Annemarie"}; // short string
string s2 {"Annemarie Stroustrup"}; // long string

// To handle multiple character sets, string is really an alias for a general template basic_string
// with the character type char:
template<typename Char>
class basic_string {
    // ... string of Char ...
};
using string = basic_string<char>;
// A user can define strings of arbitrary character types. For example, assuming we have a Japanese
// character type Jchar, we can write:
using Jstring = basic_string<Jchar>;
// Now we can do all the usual string operations on Jstring, a string of Japanese characters.