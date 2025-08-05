// Many algorithms return iterators:
bool has_c(const string& s, char c) { // does s contain the character c?
    auto p = find(s.begin(),s.end(),c);
    return p!=s.end();
}

bool has_c_short(const string& s, char c) { // does s contain the character c?
    return find(s,c)!=s.end();
}

// Find the location of all occurrences of a character in a string.
// We can return the set of occurrences as a vector<char∗>s.
// Returning a vector is efficient because vector provides move semantics
vector<string::iterator> find_all(string& s, char c) { // find all occurrences of c in s
    vector<char*> res;
    for (auto p = s.begin(); p!=s.end(); ++p)
        if (*p==c)
            res.push_back(&*p);
    return res;
}

// generalize find_all():
template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v) { // find all occurrences of v in c
    vector<typename C::iterator> res;
    for (auto p = c.begin(); p!=c.end(); ++p)
        if (*p==v)
            res.push_back(p);
    return res;
}

// The typename is needed to inform the compiler that C’s iterator is supposed to be a type
// and not a value of some type, say, the integer 7.
// Alternatively, we could have returned a vector of ordinary pointers to the elements:
template<typename C, typename V>
auto find_all(C& c, V v) {
    // find all occurrences of v in c
    vector<range_value_t<C>*> res;
    for (auto& x : c)
        if (x==v)
            res.push_back(&x);
    return res;
}

void test() {
    string m {"Mary had a little lamb"};
    for (auto p : find_all(m,'a')) // p is a string::iterator
        if (*p!='a')
            cerr << "string bug!\n";
    list<int> ld {1, 2, 3, 1, -11, 2};
    for (auto p : find_all(ld,1)) // p is a list<int>::iterator
        if (*p!=1)
            cerr << "list bug!\n";
    vector<string> vs {"red", "blue", "green", "green", "orange", "green"};
    for (auto p : find_all(vs,"red")) // p is a vector<string>::iterator
        if (*p!="red")
            cerr << "vector bug!\n";
    for (auto p : find_all(vs,"green"))
        *p = "vert";
}

