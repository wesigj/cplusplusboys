#include <iostream>

enum Day {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

int main() {
    Day today = Wednesday;
    std::cout << "Today is: " << today << std::endl;
    std::cout << "Is today Friday? " << (today == Friday ? "Yes" : "No") << std::endl;
    return 0;
}