// When writing out a trace message or an error message, we often want to make a source location
// part of that message. The library provides source_location for that:
const source_location loc = source_location::current();

void log(const string& mess = "", const source_location loc = source_location::current())
{
    cout << loc.file_name()
    << '(' << loc.line() << ':' << loc.column() << ") "
    << loc.function_name() << ": "
    << mess;
}

