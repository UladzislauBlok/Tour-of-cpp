// In <ostream>, the I/O stream library defines output for every built-in type.
// The operator << (‘put to’) is used as an output operator on objects of type ostream;
// cout is the standard output stream and cerr is the standard stream for reporting errors

void f() {
    cout << 10;
    int x {10};
    cout << x;
}

void h(int i)
{
    cout << "the value of i is ";
    cout << i;
    cout << '\n';
}

void h2(int i)
{
    cout << "the value of i is " << i << '\n';
}
// This h2() produces the same output as h()

void f1() {
    int b = 'b'; // note: char implicitly converted to int
    char c = 'c';
    cout << 'a' << b << c;
}
// The integer value of the character 'b' is 98, so this will output a98c.
