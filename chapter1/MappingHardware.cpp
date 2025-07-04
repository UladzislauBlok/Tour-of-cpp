void assignment() {
    int x = 2;
    int y = 3;
    x = y; // x becomes 3; so we get x==y

    int x = 2;
    int y = 3;
    int* p = &x;
    int* q = &y; // p!=q and *p!=*q
    p = q; // p becomes &y; now p==q, so (obviously)*p==*q


    int x = 2;
    int y = 3;
    int& r = x; // r refers to x
    int& r2 = y; // r2 refers to y
    r = r2; // read through r2, write through r: x becomes 3
}

void initialization() {
    int x = 7;
    int& r {x}; // bind r to x (r refers to x)
    r = 7; // assign to whatever r refers to
    int& r2; // error: uninitialized reference
    r2 = 99; // assign to whatever r2 refers to
    int& r = x; // bind r to x (r refers to x)
}
