// In <chrono>, the standard library provides facilities for dealing with time:
// • Clocks, time_point, and duration for measuring how long some action takes, and as the basis for anything to do with time.
// • day, month, year, and weekdays for mapping time_points into our everyday lives.
// • time_zone and zoned_time to deal with differences in time reporting across the globe.

// Here is the basic way of timing some action:
void f() {
    using namespace std::chrono; // in sub-namespace std::chrono;
    auto t0 = system_clock::now();
    do_work();
    auto t1 = system_clock::now();
    cout << t1 - t0 << "\n"; // default unit: 20223[1/100000000]s
    cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n"; // specify unit: 2ms
    cout << duration_cast<nanoseconds>(t1 - t0).count() << "ns\n"; // specify unit: 2022300ns
}

// Namespace std::chrono_literals defines time-unit suffixes
void f1() {
    this_thread::sleep_for(10ms + 33us); // wait for 10 milliseconds and 33 microseconds
}

// The standard library supports calendar:
void f2() {
    auto spring_day = April / 7 / 2018;
    cout << weekday(spring_day) << '\n'; // Sat
    cout << format("{:%A}\n", weekday(spring_day)); // Saturday

    // It is possible to express invalid dates. If in doubt, check with ok():
    auto bad_day = January / 0 / 2024;
    if (!bad_day.ok())
        cout << bad_day << " is not a valid day\n";
}

// A time_zone is a time relative to a standard (called GMT or UTC) used by the system_clock
// Timezones support:
void f3() {
    auto tp = system_clock::now(); // tp is a time_point
    cout << tp << '\n'; // 2021-11-27 21:36:08.2085095
    zoned_time ztp { current_zone(),tp }; // 2021-11-27 16:36:08.2085095 EST
    cout << ztp << '\n';
    const time_zone est {"Europe/Copenhagen"};
    cout << zoned_time{ &est,tp } << '\n'; // 2021-11-27 22:36:08.2085095 GMT+1
}