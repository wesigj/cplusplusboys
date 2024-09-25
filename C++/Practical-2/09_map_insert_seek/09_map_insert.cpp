#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> dictionary;

    // 插入元素
    dictionary.insert(std::make_pair(1, "one"));
    dictionary.insert(std::make_pair(2, "two"));
    dictionary.insert(std::make_pair(3, "three"));

    // 另一种插入方式
    dictionary[4] = "four";

    // 插入已存在键的值，会更新该键的值
    dictionary[2] = "two updated";
}