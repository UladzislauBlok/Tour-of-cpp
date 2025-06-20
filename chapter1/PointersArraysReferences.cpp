#include <iostream>
#include <vector>
char v[6]; // array of 6 characters
char* p; // pointer to character
char* p = &v[3]; // p points to v’s fourth element
char x = *p; // *p is the object that p points to

void print()
{
    int v1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto i=0; i!=10; ++i) // print elements
        std::cout << v[i] << '\n';
    // ...
}

void print2()
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto x : v) // for each x in v
        std::cout << x << '\n';
    for (auto x : {10, 21, 32, 43, 54, 65}) // for each integer in the list
        std::cout << x << '\n';
    // ...
}

void increment()
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto& x : v) // add 1 to each x in v
        ++x;
    // ...
}

// When we don’t want to modify an argument but still don’t want the cost of copying, we use a const reference (§1.6); that is, a reference to a const. For example:
double sum(const std::vector<double>&);

T a[n]; // T[n]: a is an array of n Ts
T* p; // T*: p is a pointer to T
T& r; // T&: r is a reference to T
T f(A); // T(A): f is a function taking an argument of type A returning a result of type T

double* pd = nullptr;
Link<Record>* lst = nullptr; // pointer to a Link to a Record
int x = nullptr; // error: nullptr is a pointer not an integer

int count_x_for(const char* p, char x)
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or to nothing)
{
    if (p==nullptr)
        return 0;
    int count = 0;
    for (; *p!=0; ++p)
        if (*p==x)
            ++count;
    return count;
}

int count_x_while(const char* p, char x)
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or to nothing)
{
    if (p==nullptr)
        return 0;
    int count = 0;
    while (*p) {
        if (*p==x)
            ++count;
        ++p;
    }
    return count;
}