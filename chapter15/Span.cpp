// A span gives access to a contiguous sequence of elements.
// The elements can be stored in many ways, including in vectors and built-in arrays.
// Like a pointer, a span does not own the characters to which it points
// Consider a common interface style:
void fpn(int* p, int n)
{
    for (int i = 0; i<n; ++i)
        p[i] = 0;
}
// It can be wrong:
void use(int x)
{
    int a[100];
    fpn(a,100); // OK
    fpn(a,1000); // oops, my finger slipped! (range error in fpn)
    fpn(a+10,100); // range error in fpn
    fpn(a,x); // suspect, but looks innocent
}

// We can do better using a span:
void fs(span<int> p)
{
    for (int& x : p)
        x = 0;
}
// We can use fs like this:
void use(int x)
{
    int a[100];
    fs(a); // implicitly creates a span<int>{a,100}
    fs(a,1000); // error: span expected
    fs({a+10,100}); // a range error in fs
    fs({a,x}); // obviously suspect
}

