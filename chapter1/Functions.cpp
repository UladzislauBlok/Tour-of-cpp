#include <string>
#include <vector>

char* next_char(); // no argument; return a pointer to char (a char*)
void exit(int); // int argument; return nothing
double sqrt(double); // double argument; return a double
double s2 = sqrt(2); // call sqrt() with the argument double{2}
double get(const std::vector<double>& vec, int index); // type: double(const vector<double>&,int)
char& String::operator[](int index); // type: char& String::(int)

// Overloading
void print(int); // takes an integer argument
void print(double); // takes a floating-point argument
void print(std::string); // takes a string argument
void user()
{
    print(42); // calls print(int)
    print(9.65); // calls print(double)
    print("Barcelona"); // calls print(string)
}