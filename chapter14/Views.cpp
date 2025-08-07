// A view is a way of looking at a range.
void user(forward_range auto& r)
{
    filter_view v {r, [](int x) { return x%2; } }; // view (only) odd numbers from r
    cout << "odd numbers: ";
    for (int x : v)
        cout << x << ' ';
}

// When reading from a filter_view, we read from its range. If the value read matches the predicate,
// it is returned; otherwise, the filter_view tries again with the next element from the range.
// Many ranges are infinite. Also, we often only want a few values.
// Consequently, there are views for taking only a few values from a range:
void user(forward_range auto& r)
{
    filter_view v{r, [](int x) { return x%2; } }; // view (only) odd numbers in r
    take_view tv {v, 100 }; // view at most 100 element from v
    cout << "odd numbers: ";
    for (int x : tv)
        cout << x << ' ';
}

// The key difference is that a view doesn’t own its elements;
// it is not responsible for deleting the elements of its underlying range - that’s the range’s responsibility.
// On the other hand, a view must not outlive its range:
auto bad()
{
    vector v = {1, 2, 3, 4};
    return filter_view{v,odd}; // v will be destroyed before the view
}

struct Reading {
    int location {};
    int temperature {};
    int humidity {};
    int air_pressure {};
    // ...
};

int average_temp(vector<Reading> readings)
{
    if (readings.size()==0) throw No_readings{};
    double s = 0;
    for (int x: views::elements<1>(readings)) // look at just the temperatures
        s += x;
    return s/readings.size();
}