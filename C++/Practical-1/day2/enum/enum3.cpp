#include <iostream>

enum class Season {
    Spring,
    Summer,
    Autumn,
    Winter
};

int main() {
    Season favSeason = Season::Autumn;
    switch (favSeason) {
    case Season::Spring:
        std::cout << "Spring is the season of renewal." << std::endl;
        break;
    case Season::Summer:
        std::cout << "Summer is the season of heat." << std::endl;
        break;
    case Season::Autumn:
        std::cout << "Autumn is the season of harvest." << std::endl;
        break;
    case Season::Winter:
        std::cout << "Winter is the season of cold." << std::endl;
        break;
    }
    return 0;
}