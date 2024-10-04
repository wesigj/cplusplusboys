#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 在尾部添加元素
    vec.push_back(6);

    // 访问元素
    std::cout << "Element at index 2: " << vec[2] << std::endl;

    // 遍历 vector
    for (int num : vec) { std::cout << num << " "; }
    std::cout << std::endl;

    // 删除特定索引的元素
    vec.erase(vec.begin() + 2);

    // 再次遍历 vector
    for (int num : vec) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}