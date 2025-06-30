// Enum classes:
enum class Color { red, blue, green };

enum class Traffic_light { green, yellow, red };

// Note that enumerators (e.g., red) are in the scope of their enum class, so that they can be used repeatedly in different enum classes without confusion.
Color col = Color::red;
Traffic_light light = Traffic_light::red;

// The class after the enum specifies that an enumeration is strongly typed and that its enumerators are scoped.
// Being separate types, enum classes help prevent accidental misuses of constants.
// In particular, we cannot mix Traffic_light and Color values:
Color x1 = red; // error: which red?
Color y2 = Traffic_light::red; // error: that red is not a Color
Color z3 = Color::red; // OK
auto x4 = Color::red; // OK: Color::red is a Color

// Similarly, we cannot implicitly mix Color and integer values:
int i = Color::red; // error: Color::red is not an int
Color c = 2; // initialization error: 2 is not a Color

// We can initialize enum with int
Color x = Color{5}; // OK, but verbose
Color y {6}; // also OK

// Similarly, we can explicitly convert an enum value to its underlying type:
int x = int(Color::red);

// By default, an enum class has assignment, initialization, and comparisons (e.g., == and <)
// defined, and only those. However, an enumeration is a user-defined type, so we can define operators for it
Traffic_light& operator++(Traffic_light& t) // prefix increment: ++
{
    switch (t) {
        case Traffic_light::green: return t=Traffic_light::yellow;
        case Traffic_light::yellow: return t=Traffic_light::red;
        case Traffic_light::red: return t=Traffic_light::green;
    }
}

auto signal = Traffic_light::red;
Traffic_light next = ++signal; // next becomes Traffic_light::green

// If the repetition of the enumeration name, Traffic_light, becomes too tedious, we can abbreviate it in a scope:
Traffic_light& operator++(Traffic_light& t) // prefix increment: ++
{
    using enum Traffic_light; // here, we are using Traffic_light
    switch (t) {
        case green: return t=yellow;
        case yellow: return t=red;
        case red: return t=green;
    }
}

// The enumerators from a ‘plain’ enum are entered into the same scope as the name of their enum and implicitly convert to their integer values.
enum Color { red, green, blue };
int col = green;
// Here col gets the value 1. By default, the integer values of enumerators start with 0 and increase by one for each additional enumerator.