/*
A declaration introduces its name into a scope:
• Local scope: A name declared in a function (§1.3) or lambda (§7.3.2) is called a local name.
    Its scope extends from its point of declaration to the end of the block in which its declaration occurs.
    A block is delimited by a { } pair. Function argument names are considered local names.
• Class scope: A name is called a member name (or a class member name) if it is defined in a class (§2.2, §2.3, Chapter 5), outside any function (§1.3), lambda (§7.3.2), or enum class (§2.4).
    Its scope extends from the opening { of its enclosing declaration to the matching }.
• Namespace scope: A name is called a namespace member name if it is defined in a namespace (§3.3) outside any function, lambda (§7.3.2), class (§2.2, §2.3, Chapter 5), or enum class (§2.4).
    Its scope extends from the point of declaration to the end of its namespace.
*/

#include <string>
#include <vector>
std::vector<int> vec; // vec is global (a global vector of integers)
void fct(int arg) // fct is global (names a global function)
// arg is local (names an integer argument)
{
    std::string motto {"Who dares wins"}; // motto is local
    // An object created by new ‘lives’ until destroyed by delete
    auto p = new Record{"Hume"}; // p points to an unnamed Record (created by new)
    // ...
}

struct Record {
    std::string name; // name is a member of Record (a string member)
    // ...
};