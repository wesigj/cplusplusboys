#include <iostream>

class Animal {
public:
    virtual void speak() const {
        std::cout << "Animal makes a sound" << std::endl;
    }
    virtual ~Animal() {
    } // 虚析构函数确保派生类对象的正确清理
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog barks" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Cat meows" << std::endl;
    }
};

int main() {
    Animal *myAnimal = new Dog();
    myAnimal->speak(); // 输出 "Dog barks"

    Animal *anotherAnimal = new Cat();
    anotherAnimal->speak(); // 输出 "Cat meows"

    delete myAnimal;
    delete anotherAnimal;
    return 0;
}