namespace My_code {
    class complex {
        // ...
    };

    complex sqrt(complex);

    // ...
    int main();
}

int My_code::main() {
    complex z{1, 2};
    auto z2 = sqrt(z);
    std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
    // ...
}

int main() {
    return My_code::main();
}

void my_code(vector<int>& x, vector<int>& y)
{
    using std::swap; // make the standard-library swap available locally
    // ...
    swap(x,y); // std::swap()
    other::swap(x,y); // some other swap()
    // ...
}
