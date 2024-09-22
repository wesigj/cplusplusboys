#include <iostream>
#include <vector>

template <template <typename> class TT>
class Wrapper {
    TT<int> var;

public:
    Wrapper() :
        var() {
    }
};

// 使用Wrapper
Wrapper<std::vector> w;
