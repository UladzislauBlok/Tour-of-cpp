// The standard library offers string_view; a string_view is basically a (pointer,length) pair denoting a sequence of characters

string cat(string_view sv1, string_view sv2) {
    string res {sv1}; // initialize from sv1
    return res += sv2; // append from sv2 and return
}
// We can call this cat():
string king = "Harold";
auto s1 = cat(king,"William"); // HaroldWilliam: string and const char*
auto s2 = cat(king,king); // HaroldHarold: string and string
auto s3 = cat("Edward","Stephen"sv); // EdwardStephen: const char * and string_view
auto s4 = cat("Canute"sv,king); // CanuteHarold
auto s5 = cat({&king[0],2},"Henry"sv); // HaHenry
auto s6 = cat({&king[0],2},{&king[2],4}); // Harold
// This cat() has three advantages over the compose() that takes const string& arguments (§10.2):
// • It can be used for character sequences managed in many different ways.
// • We can easily pass a substring.
// • We don’t have to create a string to pass a C-style string argument.
// Note the use of the sv (‘string view’) suffix. To use that, we need to make it visible:
using namespace std::literals::string_view_literals;

// A string_view defines a range, so we can traverse its characters. For example:
void print_lower(string_view sv1) {
    for (char ch : sv1)
        cout << tolower(ch);
}
// One significant restriction of string_view is that it is a read-only view of its characters.
// For example, you cannot use a string_view to pass characters to a function that modifies its argument to lowercase.

// Think of string_view as a kind of pointer; to be used, it must point to something:
string_view bad() {
    string s = "Once upon a time";
    return {&s[5],4}; // bad: returning a pointer to a local
}
// Here, the returned string will be destroyed before we can use its characters.