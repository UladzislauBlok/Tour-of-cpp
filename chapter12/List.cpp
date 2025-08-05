// The standard library offers a doubly-linked list called list:
void f() {
    list<Entry> phone_book = {
        {"David Hume",123456},
        {"Karl Popper",234567},
        {"Bertrand Arthur William Russell",345678}
    };
}

int get_number(const string& s) {
    for (const auto& x : phone_book)
        if (x.name==s)
            return x.number;
    return 0; // use 0 to represent "number not found"
}

// We may want to delete an element or insert a new element before it. To do that we use an iterator
int get_number(const string& s) {
    for (auto p = phone_book.begin(); p!=phone_book.end(); ++p)
        if (p->name==s)
            return p->number;
    return 0; // use 0 to represent "number not found"
}

// Adding elements to a list and removing elements from a list is easy:
void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q) {
    phone_book.insert(p,ee); // add ee before the element referred to by p
    phone_book.erase(q); // remove the element referred to by q
}

