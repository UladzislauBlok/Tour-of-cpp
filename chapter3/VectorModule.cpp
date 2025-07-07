//Using modules, we don’t have to complicate our code to hide implementation details from users;
//a module will only grant access to exported declarations
//The way we use this module is to import it where we need it
export module Vector; // defining the module called "Vector"
export class Vector {
public:
    Vector(int s);

    double &operator[](int i);

    int size();

private:
    double∗*elem; // elem points to an array of sz doubles
    int sz;
};

Vector::Vector(int s)
    : elem{new double[s]}, sz{s} // initialize members
{
}

double &Vector::operator[](int i) {
    return elem[i];
}

int Vector::size() {
    return sz;
}

export bool operator==(const Vector &v1, const Vector &v2) {
    if (v1.size() != v2.size())
        return false;
    for (int i = 0; i < v1.size(); ++i)
        if (v1[i] != v2[i])
            return false;
    return true;
}
