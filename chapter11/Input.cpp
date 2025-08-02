// In <istream>, the standard library offers istreams for input.
// Like ostreams, istreams deal with character string representations of built-in types and can easily be extended to cope with user-defined types.
// The operator >> (‘get from’) is used as an input operator; cin is the standard input stream.

void f() {
    int i;
    cin >> i; // read an integer into i
    double d;
    cin >> d; // read a double-precision floating-point number into d
}

void f1() {
    int i;
    double d;
    cin >> i >> d; // read into i and d
}

// Read into a string.
void f3() {
    cout << "Please enter your name\n";
    string str;
    cin >> str;
    cout << "Hello, " << str << "!\n";
}
// If you type in Eric the response is:
// Hello, Eric!

// By default, a whitespace character, such as a space or a newline, terminates the read,
// so if you enter 'Eric Bloodaxe' pretending to be the ill-fated king of York, the response is still:
// Hello, Eric!
// You can read a whole line using the getline() function. For example:
void f4() {
    cout << "Please enter your name\n";
    string str;
    getline(cin,str);
    cout << "Hello, " << str << "!\n";
}

