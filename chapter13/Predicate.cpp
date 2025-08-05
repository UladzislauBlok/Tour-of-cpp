// A map allows us to access its elements as a sequence of (key,value) pairs, so we can search a map<string,int>’s sequence
// for a pair<const string,int> where the int is greater than 42:
void f(map<string,int>& m) {
    auto p = find_if(m,Greater_than{42});
    // ...
}

struct Greater_than {
    int val;
    Greater_than(int v) : val{v} { }
    bool operator()(const pair<string,int>& r) const { return r.second>val; }
};
// Alternatively and equivalently, we could use a lambda expression:
auto p = find_if(m, [](const auto& r) { return r.second>42; });
// A predicate should not modify the elements to which it is applied