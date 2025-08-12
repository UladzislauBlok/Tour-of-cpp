// Consider the classical ‘draw all shapes’ example:
void draw_all(vector<Shape*>& v)
{
    for_each(v.begin(),v.end(),[](Shape* p) { p->draw(); });
}
// Like all standard-library algorithms, for_each() calls its argument using the traditional function call
// syntax f(x), but Shape's draw() uses the conventional object-oriented notation x->f().
// A lambda easily mediates between the two notations.

// the function adaptor mem_fn(mf) produces a function object that can be called as a nonmember function.
void draw_all(vector<Shape*>& v)
{
    for_each(v.begin(),v.end(),mem_fn(&Shape::draw));
}

// The standard-library function is a type that can hold any object you can invoke using the call operator ().
// That is, an object of type function is a function object
void f1() {
    int f1(double);
    function<int(double)> fct1 {f1}; // initialize to f1
    int f2(string);
    function fct2 {f2}; // fct2’s type is function<int(string)>
    function fct3 = [](Shape* p) { p->draw(); }; // fct3’s type is function<void(Shape*)>
}

