#include <iostream>

// 基类
class Animal {
public:
    virtual void speak() const {
        std::cout << "The animal makes a sound." << std::endl;
    }

    virtual ~Animal() {
    } // 虚析构函数
};

// 派生类：狗
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "The dog barks." << std::endl;
    }
};

// 派生类：猫
class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "The cat meows." << std::endl;
    }
};

int main() {
    Animal *myAnimal = nullptr;

    Dog myDog;
    myAnimal = &myDog;
    myAnimal->speak(); // 输出: The dog barks.

    Cat myCat;
    myAnimal = &myCat;
    myAnimal->speak(); // 输出: The cat meows.

    return 0;
}