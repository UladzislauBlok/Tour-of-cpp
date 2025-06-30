#include <iostream>
#include <string>
#include <variant>
//A union is a struct in which all members are allocated at the same address so that the union occupies only as much space as its largest member.
//Naturally, a union can hold a value for only one member at a time. For example, consider a symbol table entry that holds a name and a value.
//The value can either be a Node∗ or an int:
enum class Type { ptr, num }; // a Type can hold values ptr and num (§2.4)
struct Entry {
    std::string name; // string is a standard-library type
    Type t;
    Node* p; // use p if t==Type::ptr
    int i; // use i if t==Type::num
};

void f(Entry* pe)
{
    if (pe->t == Type::num)
        std::cout << pe->i;
}

// The members p and i are never used at the same time, so space is wasted. It can be easily recovered by specifying that both should be members of a union, like this:
union Value {
    Node* p;
    int i;
};

// Now Value::p and Value::i are placed at the same address of memory of each Value object.
// This kind of space optimization can be important for applications that hold large amounts of memory so that compact representation is critical.
// The language doesn’t keep track of which kind of value is held by a union, so the programmer must do that:
struct Entry {
    std::string name;
    Type t;
    Value v; // use v.p if t==Type::ptr; use v.i if t==Type::num
};

void f(Entry* pe)
{
    if (pe->t == Type::num)
        std::cout << pe->v.i;
}

// The standard library type, variant, can be used to eliminate most direct uses of unions.
// A variant stores a value of one of a set of alternative types.
// For example, a variant<Node∗,int> can hold either a Node∗ or an int. Using variant, the Entry example could be written as:
struct Entry {
    std::string name;
    std::variant<Node*,int> v;
};

void f(Entry* pe)
{
    if (holds_alternative<int>(pe->v)) // does *pe hold an int? (see §15.4.1)
        std::cout << std::get<int>(pe->v); // get the int
}
// For many uses, a variant is simpler and safer to use than a union.