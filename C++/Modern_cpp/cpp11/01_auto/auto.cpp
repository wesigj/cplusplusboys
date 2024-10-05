template <typename T, typename U>
auto add(T x, U y) -> decltype(x + y) {
    return x + y;
}