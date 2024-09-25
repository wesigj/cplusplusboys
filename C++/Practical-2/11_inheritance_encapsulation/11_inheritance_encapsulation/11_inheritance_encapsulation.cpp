#include <iostream>
#include <string>

class Animal {
private:
    std::string name;

protected:
    std::string sound;

public:
    Animal(const std::string &n) : name(n) {
    }
    virtual void makeSound() const { /* ... */
    }
    virtual ~Animal() {
    } // 虚析构函数以确保派生类的正确清理
};

class Dog : public Animal {
private:
    int legs;

public:
    Dog(const std::string &n, int l) : Animal(n), legs(l) {
    }
    void makeSound() const override { /* 汪汪汪 */
    }
    // ... 其他成员函数 ...
};

// ...
int main() {
    Dog myDog("Bobby", 4);
    myDog.makeSound(); // 调用 Dog 类的 makeSound 函数
}
