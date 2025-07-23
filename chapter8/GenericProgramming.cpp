double sum(const vector<int>& v) {
    double res = 0;
    for (auto x : v)
        res += x;
    return res;
}
// This is obviously one of many ways to compute the sum of a sequence of numbers.
// Consider what makes this code less general than it needs to be:
// • Why just ints?
// • Why just vectors?
// • Why accumulate in a double?
// • Why start at 0?
// • Why add?
// Answering the first four questions by making the concrete types into template arguments, we get
// the simplest form of the standard-library accumulate algorithm:
template<forward_iterator Iter, Arithmetic<iter_value_t<Iter>> Val>
Val accumulate(Iter first, Iter last, Val res) {
    for (auto p = first; p!=last; ++p)
        res += *p;
    return res;
}
// Here, we have:
// • The data structure to be traversed has been abstracted into a pair of iterators representing asequence
// • The type of the accumulator has been made into a parameter.
// • The type of the accumulator must be arithmetic .
// • The type of the accumulator must work with the iterator’s value type (the element type of the sequence).
// • The initial value is now an input; the type of the accumulator is the type of this initial value

// Naturally, the repetition of begin() and end() is tedious, so we can simplify the user interface a bit:
template<forward_range R, Arithmetic<value_type_t<R>> Val>
Val accumulate(const R& r, Val res = 0) {
    for (auto x : r)
        res += x;
    return res;
}

// Both the pair-of-iterators and the range version of accumulate() are useful: the pair-of-iterators
// version for generality, the range version for simplicity of common uses.