// It has been credibly argued that printf() is the most popular function in C and a significant factor in its success
void f() {
    printf("an int %g and a string '%s'\n", 123, "Hello!");
}

// In <format>, the standard library provides a type-safe printf()-style formatting mechanism.
// The basic function, format() produces a string:
void f1() {
    string s = format("Hello, {}\n", val);
}

// The most common use of format() is to output its result:
void f2() {
    cout << format("Hello, {}\n", val);
}

// To see how this works, let’s first repeat the examples from:
void f3() {
    cout << format("{} {:x} {:o} {:d} {:b}\n", 1234, 1234, 1234, 1234, 1234);
}
// This gives the same output:
// 1234 4d2 2322 1234 10011010010
// A formatting directive is preceded by a colon.
// The integer formatting alternatives are x for hexadecimal, o for octal, d for decimal, and b for binary

// By default, format() takes its arguments in order. However, we can specify an arbitrary order.
void f4() {
    cout << format("{3:} {1:x} {2:o} {0:b}\n", 000, 111, 222, 333);
}
// This prints
// 333 6f 336 0.

// The floating-point formats are the same as for ostream: e for scientific, a for hexfloat, f for fixed, and g for default.
void f5() {
    cout << format("{0:}; {0:e}; {0:a}; {0:f}; {0:g}\n", 123.456); // default, scientific, hexfloat, fixed, default
}
// The result was identical to that from ostream except that the hexadecimal number was not preceded by 0x:
// 123.456; 1.234560e+002; 1.edd2f2p+6; 123.456000; 123.456

// A dot precedes a precision specifier:
void f6() {
    cout << format("precision(8): {:.8} {} {}\n", 1234.56789, 1234.56789, 123456);
    cout << format("precision(4): {:.4} {} {}\n", 1234.56789, 1234.56789, 123456);
    cout << format("{}\n", 1234.56789);
}
// Unlike for streams, specifiers are not ‘sticky’ so we get:
// precision(8): 1234.5679 1234.56789 123456
// precision(4): 1235 1234.56789 123456
// 1234.56789
// As with stream formatters, we can also specify the size of the field into which a number is to be
// placed and its alignment in that field.

// Like stream formatters, format() can also handle time and dates
void f7() {
    cout << format("birthday: {}\n",November/28/2021);
    cout << format("zt: {}", zoned_time{current_zone(), system_clock::now()});
}
// As usual, the default formatting of values is identical to that of default stream output formatting.

// However, format() offers a non-extensible mini-language of about 60 format specifiers allowing very
// detailed control over formatting of numbers and dates.

void f8() {
    auto ymd = 2021y/March/30 ;
    cout << format("ymd: {3:%A},{1:} {2:%B},{0:}\n", ymd.year(), ymd.month(), ymd.day(), weekday(ymd));
}
// This produced:
// ymd: Tuesday, March 30, 2021

// All time and date format strings start with %.
// The flexibility offered by the many format specifiers can be important, but it comes with many
// opportunities for mistakes. Some specifiers come with optional or locale dependent semantics.
// If a formatting error is caught at run time, a format_error exception is thrown.
void f9() {
    string ss = format("{:%F}", 2); // error: mismatched argument; potentially caught at compile time
    string sss = format("{%F}", 2); // error: bad format; potentially caught at compile time
}
// The examples so far have had constant formats that can be checked at compile time.
// The complimentary function vformat() takes a variable as a format to significantly increase flexibility
// and the opportunities for run-time errors:
void f10() {
    string fmt = "{}";
    cout << vformat(fmt, make_format_args(2)); // OK
    fmt = "{:%F}";
    cout << vformat(fmt, make_format_args(2)); // error: format and argument mismatch; caught at run time
}

// Finally, a formatter can also write directly into a buffer defined by an iterator.
void f11() {
    string buf;
    format_to(back_inserter(buf), "iterator: {} {}\n", "Hi! ", 2022);
    cout << buf; // iterator: Hi! 2022
}
// This gets interesting for performance if we use a stream’s buffer directly or the buffer for some other output device.
