void f()
{
    path f = "dir/hypothetical.cpp"; // naming a file
    assert(exists(f)); // f must exist
    if (is_regular_file(f)) // is f an ordinary file?
        cout << f << " is a file; its size is " << file_size(f) << '\n';
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "arguments expected\n";
        return 1;
    }
    path p {argv[1]}; // create a path from the command line
    cout << p << " " << exists(p) << '\n'; // note: a path can be printed like a string
    // ...
}

// A path is not checked for validity until it is used.
// Even then, its validity depends on the conventions of the system on which the program runs.
// Naturally, a path can be used to open a file
void use(path p)
{
    ofstream f {p};
    if (!f) error("bad file name: ", p);
    f << "Hello, file!";
}

void print_directory(path p) {
    // print the names of all files in p
    try
    {
        if (is_directory(p)) {
            cout << p << ":\n";
            for (const directory_entry& x : directory_iterator{p})
                cout << " " << x.path() << '\n';
        }
    }
    catch (const filesystem_error& ex) {
        cerr << ex.what() << '\n';
    }
}

void use()
{
    print_directory("."); // current directory
    print_directory(".."); // parent directory
    print_directory("/"); // Unix root directory
    print_directory("c:"); // Windows volume C
    for (string s; cin>>s; )
        print_directory(s);
}

void test(path p)
{
    if (is_directory(p)) {
        cout << p << ":\n";
        for (const directory_entry& x : directory_iterator(p)) {
            const path& f = x; // refer to the path part of a directory entry
            if (f.extension() == ".exe")
                cout << f.stem() << " is a Windows executable\n";
            else {
                string n = f.extension().string();
                if (n == ".cpp" || n == ".C" || n == ".cxx")
                    cout << f.stem() << " is a C++ source file\n";
            }
        }
    }
}
// We use a path as a string (e.g., f.extension) and we can extract strings of various types from a path (e.g., f.extension().string())