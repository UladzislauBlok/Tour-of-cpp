// In <regex>, the standard library provides support for regular expressions in the form of the std::regex class and its supporting functions.
regex pat {R"(\w{2}\s∗\d{5}(-\d{4})?)"}; // U.S. postal code pattern: XXddddd-dddd and variants
// raw string literal starting with R"( and terminated by )"

// In <regex>, the standard library provides support for regular expressions:
// • regex_match(): Match a regular expression against a string (of known size)
// • regex_search(): Search for a string that matches a regular expression in an (arbitrarily long) stream of data
// • regex_replace(): Search for strings that match a regular expression in an (arbitrarily long) stream of data and replace them.
// • regex_iterator: Iterate over matches and submatches
// • regex_token_iterator: Iterate over non-matches.

// The simplest way of using a pattern is to search for it in a stream:
void f() {
    int lineno = 0;
    for (string line; getline(cin,line); ) { // read into line buffer
        ++lineno;
        smatch matches; // matched strings go here
        if (regex_search(line,matches,pat)) // search for pat in line
            cout << lineno << ": " << matches[0] << '\n';
    }
}

void use() {
    ifstream in("file.txt"); // input file
    if (!in) { // check that the file was opened
        cerr << "no file\n";
        return;
    }
    regex pat {R"(\w{2}\s∗\d{5}(-\d{4})?)"}; // U.S. postal code pattern
    int lineno = 0;
    for (string line; getline(in,line); ) {
        ++lineno;
        smatch matches; // matched strings go here
        if (regex_search(line, matches, pat)) {
            cout << lineno << ": " << matches[0] << '\n'; // the complete match
            if (1<matches.size() && matches[1].matched) // if there is a sub-pattern
                // and if it is matched
                    cout << "\t: " << matches[1] << '\n'; // submatch
        }
    }
}
// This function reads a file looking for U.S. postal codes, such as TX77845 and DC 20500-0001.
// An smatch type is a container of regex results. Here, matches[0] is the whole pattern and matches[1] is
// the optional four-digit subpattern (-\d{4})?

// We can define a regex_iterator for iterating over a sequence of characters finding matches for a pat-
// tern. For example, we can use a sregex_iterator (a regex_iterator<string>) to output all whitespace-
// separated words in a string:
void test() {
    string input = "aa as; asd ++eˆasdf asdfg";
    regex pat {R"(\s+(\w+))"};
    for (sregex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
        cout << (*p)[1] << '\n';
}
// This outputs:
// as
// asd
// asdfg


