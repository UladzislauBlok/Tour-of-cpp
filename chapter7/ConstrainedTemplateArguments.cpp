// For all T such that Element(T)
// Such a predicate is called a concept
// A template argument for which a concept is specified is called a constrained argument and a template
// for which an argument is constrained is called a constrained template.

template<Element T>
class Vector {
private:
    T* elem; // elem points to an array of sz elements of type T
    int sz;
    // ...
};
