#include <vector>
#include <list>
#include <functional>
#include <iostream>

template <typename K, typename V>
class HashTable {
public:
    // 构造函数，初始化一个指定大小的哈希表
    explicit HashTable(size_t size) : table(size) {
    }

    // 插入键值对
    void insert(const K &key, const V &value) {
        auto &bucket = table[bucket_index(key)];
        for (auto &pair : bucket) {
            if (pair.first == key) {
                pair.second = value; // 如果键已存在，则更新值
                return;
            }
        }
        bucket.push_back({key, value}); // 否则，在链表尾部插入新元素
    }

    // 按键查找值
    V *find(const K &key) {
        auto &bucket = table[bucket_index(key)];
        for (auto &pair : bucket) {
            if (pair.first == key) {
                return &pair.second; // 找到键，返回值的指针
            }
        }
        return nullptr; // 未找到键，返回nullptr
    }

    // 删除键值对
    void remove(const K &key) {
        auto &bucket = table[bucket_index(key)];
        auto  it     = std::find_if(
            bucket.begin(), bucket.end(),
            [&key](const std::pair<K, V> &pair) { return pair.first == key; });
        if (it != bucket.end()) {
            bucket.erase(it); // 找到元素，从链表中移除
        }
    }

private:
    // 哈希函数，返回一个键的索引位置
    size_t bucket_index(const K &key) const {
        return std::hash<K>()(key) % table.size();
    }

    // 哈希表的存储，使用链表解决冲突
    std::vector<std::list<std::pair<K, V>>> table;
};

int main() {
    HashTable<int, std::string> hash_table(10); // 创建一个大小为10的哈希表

    hash_table.insert(1, "Kimi");
    hash_table.insert(2, "Moonshot AI");

    if (auto *value = hash_table.find(1)) {
        std::cout << "Found: " << *value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    hash_table.remove(1);

    if (auto *value = hash_table.find(1)) {
        std::cout << "Found: " << *value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}