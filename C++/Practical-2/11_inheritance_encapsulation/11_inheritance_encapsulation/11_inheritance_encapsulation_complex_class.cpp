#include <iostream>
#include <string>

// 基类：Vehicle
class Vehicle {
protected:
    std::string brand;
    std::string model;
    int         year;

public:
    Vehicle(const std::string &brand, const std::string &model, int year) :
        brand(brand), model(model), year(year) {
    }

    virtual void display() const {
        std::cout << "Brand: " << brand << ", Model: " << model
                  << ", Year: " << year << std::endl;
    }

    virtual ~Vehicle() {
    }
};

// 派生类：Car
class Car : public Vehicle {
protected:
    int    doors;
    double fuelCapacity;

public:
    Car(const std::string &brand, const std::string &model, int year, int doors,
        double fuelCapacity) :
        Vehicle(brand, model, year), doors(doors), fuelCapacity(fuelCapacity) {
    }

    // 添加 override 关键字
    void display() const override { // 注意这里还添加了 const 关键字
        Vehicle::display();
        std::cout << "Doors: " << doors << ", Fuel Capacity: " << fuelCapacity
                  << " liters" << std::endl;
    }
};

// 组合：Engine
class Engine {
private:
    std::string type;
    double      horsepower;

public:
    Engine(const std::string &type, double horsepower) :
        type(type), horsepower(horsepower) {
    }

    void display() const {
        std::cout << "Engine Type: " << type << ", Horsepower: " << horsepower
                  << std::endl;
    }
};

// 派生类：SportsCar
class SportsCar : public Car {
private:
    Engine engine;
    bool   hasSpoiler;

public:
    SportsCar(const std::string &brand, const std::string &model, int year,
              int doors, double fuelCapacity, const std::string &engineType,
              double horsepower, bool hasSpoiler) :
        Car(brand, model, year, doors, fuelCapacity),
        engine(engineType, horsepower), hasSpoiler(hasSpoiler) {
    }

    void display() const override {
        Car::display();
        engine.display();
        std::cout << "Sports Features: ";
        if (hasSpoiler) { std::cout << "Spoiler"; }
        std::cout << std::endl;
    }
};

int main() {
    // 创建一个 SportsCar 对象
    SportsCar sportsCar("Ford", "Mustang", 2021, 2, 50.0, "V8", 450, true);

    // 显示汽车信息
    sportsCar.display();

    return 0;
}