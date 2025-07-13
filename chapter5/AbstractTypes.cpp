class Container {
public:
    // Function with virtual table (vtbl), that can be overridden in future
    virtual double &operator[](int) = 0; // pure virtual function
    virtual int size() const = 0; // const member function
    virtual ˜Container() {
    } // destructor
};

Container c; // error: there can be no objects of an abstract class
Container *p = new Vector_container(10); // OK: Container is an interface for Vector_container

void use(Container &c) {
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        cout << c[i] << '\n';
}

class Vector_container : public Container {
    // Vector_container implements Container
public:
    Vector_container(int s) : v(s) {
    } // Vector of s elements
    ˜Vector_container() {
    }

    double &operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }

private:
    Vector v;
};

void g() {
    Vector_container vc(10); // Vector of ten elements
    // ... fill vc ...
    use(vc);
}

class List_container : public Container {
    // List_container implements Container
public:
    List_container() {
    } // empty List
    List_container(initializer_list<double> il) : ld{il} {
    }

    ˜List_container() {
    }

    double &operator[](int i) override;

    int size() const override { return ld.size(); }

private:
    std::list<double> ld; // (standard-library) list of doubles (§12.3)
};

double &List_container::operator[](int i) {
    for (auto &x: ld) {
        if (i == 0)
            return x;
        --i;
    }
    throw out_of_range{"List container"};
}
