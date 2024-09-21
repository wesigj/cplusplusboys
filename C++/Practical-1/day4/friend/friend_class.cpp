#include <iostream>

class Date; // 前向声明

class Newspaper {
private:
    Date        publicationDate; // Newspaper依赖于Date类
    std::string headline;

public:
    friend class Date; // 声明Date为友元类
    void printHeadline() const {
        std::cout << headline << std::endl;
    }
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) :
        day(d), month(m), year(y) {
    }

    // 访问Newspaper的私有成员
    void printPublicationDate(const Newspaper &newspaper) const {
        std::cout << "Published on: " << day << "/" << month << "/" << year << std::endl;
    }
};

int main() {
    Newspaper newspaper(Date(25, 12, 2023));
    newspaper.printHeadline();
    newspaper.publicationDate.printPublicationDate(newspaper);
    return 0;
}