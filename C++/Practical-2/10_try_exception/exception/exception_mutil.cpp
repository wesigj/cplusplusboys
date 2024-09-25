#include <iostream>
#include <stdexcept>

void mightGoWrong(int i) {
    if (i == 0)
        throw std::runtime_error("Argument is zero");
    else if (i < 0)
        throw std::invalid_argument("Argument is negative");
    else
        throw std::logic_error("Argument is too large");
}

int main() {
    try {
        mightGoWrong(-1);
    } catch (const std::runtime_error &e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::logic_error &e) {
        std::cout << "Logic error: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Unknown exception: " << e.what() << std::endl;
    }
    return 0;
}