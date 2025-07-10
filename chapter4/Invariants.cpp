Vector::Vector(int s) {
    if (s < 0)
        throw length_error{"Vector constructor: negative size"};
    elem = new double[s];
    sz = s;
}

void test(int n) {
    try {
        Vector v(n);
    } catch (std::length_error &err) {
        // ... handle negative size ...
    }
    catch (std::bad_alloc &err) {
        // ... handle memory exhaustion ...
    }
}

void run() {
    test(-27); // throws length_error (-27 is too small)
    test(1'000'000'000); // may throw bad_alloc
    test(10); // likely OK
}

void test(int n) {
    try {
        Vector v(n);
    } catch (std::length_error &) {
        // do something and rethrow
        cerr << "test failed: length error\n";
        throw; // rethrow
    }
    catch (std::bad_alloc &) {
        // ouch! this program is not designed to handle memory exhaustion
        std::terminate(); // terminate the program
    }
}
