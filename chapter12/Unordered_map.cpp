struct Record {
    string name;
    int product_code;
    // ...
};
bool operator==(const Record&, const Record&) { /* ... */ }
struct Rhash { // a hash function for Record
    size_t operator()(const Record& r) const
    {
        return hash<string>()(r.name) ˆ hash<int>()(r.product_code);
    }
};
unordered_set<Record,Rhash> my_set; // set of Records using Rhash for lookup

// We can avoid explicitly passing the hash operation by defining it as a specialization of the standard-library hash:
namespace std { // make a hash function for Record
    template<> struct hash<Record> {
        using argument_type = Record;
        using result_type = size_t;
        result_type operator()(const Record& r) const
        {
            return hash<string>()(r.name) ˆ hash<int>()(r.product_code);
        }
    };
}

