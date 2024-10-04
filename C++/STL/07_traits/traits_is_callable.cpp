#include <iostream>
#include <type_traits>
#include <utility>

// 辅助模板，用于判断可调用性
template <typename Fun, typename... Args,
          typename = decltype(std::declval<Fun>()(std::declval<Args>()...))>
std::true_type is_callable_test(int);

// 辅助模板，用于类型不可调用时的回退
template <typename, typename...>
std::false_type is_callable_test(...);

// is_callable 的包装 Traits
template <typename Fun, typename... Args>
struct is_callable {
    static constexpr bool value =
        decltype(is_callable_test<Fun, Args...>(0))::value;
};

int add(int a, int b) {
    return a + b;
}

void print(const std::string &msg) {
    std::cout << msg << std::endl;
}

struct Functor {
    void operator()(int x, int y) const {
        std::cout << "Functor called with " << x << " and " << y << std::endl;
    }
};

int main() {
    // 可调用的检测
    static_assert(is_callable<decltype(&add), int, int>::value,
                  "add 应该是可调用的");
    static_assert(
        is_callable<void (*)(const std::string &), const std::string &>::value,
        "print 应该是可调用的");
    static_assert(is_callable<Functor, int, int>::value, "Functor 应该可调用");

    // 不可调用的检测
    static_assert(!is_callable<decltype(&add), double, double>::value,
                  "add 不应该对 double 类型是可调用的");
    static_assert(!is_callable<void(int), int, int>::value,
                  "类型不匹配时不可调用");

    std::cout << "所有断言通过!" << std::endl;

    return 0;
}