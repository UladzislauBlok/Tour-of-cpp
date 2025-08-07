// operator |
// filter() yields a filter_view.
// This allows us to combine filters in a sequence rather than presenting them as a set of nested function calls.
void user(forward_range auto& r)
{
    auto odd = [](int x) { return x % 2; };
    for (int x : r | views::filter(odd) | views::take(3))
        cout << x << ' ';
}
// An input range 1 2 3 4 5 6 7 8 0 produces 1 3 5.

// 'r|f|g' means (g_filter(f_filter(r))). The initial r has to be a range or a generator.

// These filter functions are in namespace ranges::views:
void user(forward_range auto& r)
{
    for (int x : r | views::filter([](int x) { return x % 2; } ) | views::take(3) )
        cout << x << ' ';
}

// The implementation of views and pipelines involves some quite hair-raising template metaprogramming,
// so if you are concerned about performance
void user(forward_range auto& r)
{
    int count = 0;
    for (int x : r)
        if (x % 2) {
            cout << x << ' ';
            if (++count == 3) return;
        }
}

