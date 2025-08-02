// The simplest formatting controls are called manipulators and are found in <ios>, <istream>,
// <ostream>, and <iomanip> (for manipulators that take arguments). For example, we can output inte-
// gers as decimal (the default), octal, or hexadecimal numbers:
void f() {
    cout << 1234 << ' ' << hex << 1234 << ' ' << oct << 1234 << dec << 1234 << '\n'; // 1234 4d2 2322 1234
}

// We can explicitly set the output format for floating-point numbers:
constexpr double d = 123.456;

void f1() {
    cout << d << "; " // use the default format for d
            << scientific << d << "; " // use 1.123e2 style format for d
            << hexfloat << d << "; " // use hexadecimal notation for d
            << fixed << d << "; " // use 123.456 style format for d
            << defaultfloat << d << '\n'; // use the default format for d
}
// This produces:
// 123.456; 1.234560e+002; 0x1.edd2f2p+6; 123.456000; 123.456

// Floating-point values are rounded rather than just truncated, and precision() doesn’t affect integer output
void f3() {
    cout.precision(8);
    cout << "precision(8): " << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
    cout.precision(4);
    cout << "precision(4): " << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
    cout << 1234.56789 << '\n';
}
// This produces:
// precision(8): 1234.5679 1234.5679 123456
// precision(4): 1235 1235 123456
// 1235

// In addition to the basic numbers, << can also handle time and dates: duration, time_point
// year_month_date, weekday, month, and zoned_time (§16.2). For example:
void f4() {
    cout << "birthday: " << November/28/2021 << '\n';
    cout << << "zt: " << zoned_time{current_zone(), system_clock::now()} << '\n';
}
// This produced:
// birthday: 2021-11-28
// zt: 2021-12-05 11:03:13.5945638 EST

