#include <iostream>
#include <vector>

bool accept()
{
    std::cout << "Do you want to proceed (y or n)?\n"; // write question
    char answer = 0; // initialize to a value that will not appear on input
    std::cin >> answer; // read answer
    if (answer == 'y')
        return true;
    return false;
}

bool accept2()
{
    std::cout << "Do you want to proceed (y or n)?\n"; // write question
    char answer = 0; // initialize to a value that will not appear on input
    std::cin >> answer; // read answer
    switch (answer) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            std::cout << "I'll take that for a no.\n";
            return false;
    }
}

void action()
{
    while (true) {
        std::cout << "enter action:\n"; // request action
        std::string act;
        std::cin >> act; // read characters into a string
        Point delta {0,0}; // Point holds an {x,y} pair
        for (char ch : act) {
            switch (ch) {
                case 'u': // up
                case 'n': // north
                    ++delta.y;
                    break;
                case 'r': // right
                case 'e': // east
                    ++delta.x;
                    break;
                    // ... more actions ...
                    default:
                        std::cout << "I freeze!\n";
            }
            move(current+delta*scale);
            update_display();
        }
    }
}

void do_something(std::vector<int>& v)
{
    if (auto n = v.size(); n!=0) {
        // ... we get here if n!=0 ...
    }
    // ...
}

void do_something(std::vector<int>& v)
{
    if (auto n = v.size()) {
        // ... we get here if n!=0 ...
    }
    // ...
}