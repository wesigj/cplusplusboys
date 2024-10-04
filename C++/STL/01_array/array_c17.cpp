#include <array>
#include <functional>
#include <tuple>

int main() {
    std::array<int, 3> arr1 = {1, 2, 3};
    auto [a, b, c]          = arr1;

    std::array<std::function<int(int, int)>, 2> funcArr = {
        [](int, int) { return 0; }, [](int a, int b) { return a + b; }};
    auto result = std::apply(funcArr[1], std::tuple<int, int>{1, 2});

    return 0;
}