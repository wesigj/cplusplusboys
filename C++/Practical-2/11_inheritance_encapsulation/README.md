# C++ Practical-2 继承与封装

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.继承与封装

在 C++ 中，继承和封装是面向对象编程的两个基本特征。

### 1.1.封装

封装是将数据（成员变量）和操作这些数据的方法（成员函数）捆绑在一起的一种编程机制。在 C++ 中，封装通过类来实现，类可以包含私有（private）、保护（protected）和公共（public）成员。

- **私有成员**：可以被类内部的成员函数访问，不能被外部函数访问。
- **保护成员**：可以被类及其子类访问。
- **公共成员**：可以被任何函数访问。

封装的目的是隐藏对象的实现细节，只暴露出必要的接口。

```cpp
class Box {
private:
    double length; // 私有成员
    double width;
    double height;

public:
    Box(double l, double w, double h) : length(l), width(w), height(h) {} // 构造函数

    double getVolume() const { // 公共成员函数
        return length * width * height;
    }

    // ... 其他成员函数 ...
};
```

### 1.2.继承

继承是一种创建新类（称为子类或派生类）的方法，这些新类基于一个或多个现有类（称为基类或父类）。继承支持代码重用，子类继承了基类的所有属性和方法。

- **公有继承**：子类继承基类的所有公有成员和保护成员，基类的公有成员和保护成员在子类中保持原有的访问级别。
- **保护继承**：基类的公有成员和保护成员在子类中都成为保护成员。
- **私有继承**：基类的公有成员和保护成员在子类中都成为私有成员。

```cpp
class Shape {
public:
    virtual void draw() const { /* ... */ } // 公有虚函数
    // ... 其他公有成员 ...
protected:
    // ... 保护成员 ...
};

class Circle : public Shape { // 公有继承
    double radius;
public:
    Circle(double r) : radius(r) { /* ... */ }
    void draw() const override { /* ... */ } // 覆盖基类的虚函数
    // ... 其他成员函数 ...
};

class Rectangle : public Shape { // 公有继承
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) { /* ... */ }
    void draw() const override { /* ... */ } // 覆盖基类的虚函数
    // ... 其他成员函数 ...
};
```

在上面的例子中，`Shape` 是一个基类，它定义了一个虚函数 `draw()`。`Circle` 和 `Rectangle` 是从 `Shape` 派生的子类，它们覆盖了 `draw()` 函数。

### 1.3.组合使用封装和继承

在实际的应用程序中，封装和继承经常一起使用。通过封装，基类可以隐藏其内部实现细节，只暴露出必要的接口。然后，子类可以通过继承这些接口来扩展或修改基类的行为。

```cpp
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

```

在这个例子中，`Animal` 类封装了动物的名称和声音，并且提供了一个虚函数 `makeSound()`。`Dog` 类继承自 `Animal` 并添加了额外的成员变量 `legs`。`Dog` 类覆盖了 `makeSound()` 函数以提供特定的实现。

通过使用封装和继承，我们可以创建出模块化且易于维护的代码，同时还可以利用多态性来实现灵活的接口。

## 2.使用继承和组合的复杂类的例子？

以下是一个使用继承和组合的复杂类的例子。在这个例子中，我们将创建一个汽车（Car）的类层次结构，并使用组合来添加额外的功能。

```cpp
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
```

在这个例子中，我们有一个基类 `Vehicle`，它定义了汽车品牌、型号和年份。`Car` 类继承自 `Vehicle` 并添加了车门数量和燃油容量。

我们还定义了一个 `Engine` 类，它使用组合的方式被 `SportsCar` 类所包含。`Engine` 类有引擎类型和马力。`SportsCar` 类继承自 `Car` 并使用 `Engine` 类的实例作为其成员。

`SportsCar` 类还添加了一个布尔成员 `hasSpoiler` 来表示是否具有扰流板。

在 `main` 函数中，我们创建了一个 `SportsCar` 对象并调用了 `display` 方法来显示汽车的详细信息。

这个例子展示了如何在 C++ 中使用继承来创建一个类层次结构，并使用组合来添加额外的功能。通过这种方式，我们可以构建出复杂且功能丰富的类。

## 3.在C++中，如何实现多态性？

在 C++ 中，多态性是指允许不同类的对象对同一消息做出响应的能力，即同一个函数或方法在不同的对象中可以有不同的实现。C++ 支持两种主要的多态性：编译时多态性和运行时多态性。

### 3.1.编译-time Polymorphism (静态多态性)

编译时多态性主要通过函数重载（Overloading）和模板（Templates）实现。

1. **函数重载**：
   同一个作用域内的多个函数可以有相同的名称，但是参数类型、数量或顺序必须不同。

   ```cpp
    #include <iostream>

    void print(int i) {
        std::cout << "Printing int: " << i << std::endl;
    }

    void print(double f) {
        std::cout << "Printing float: " << f << std::endl;
    }

    int main() {
        print(5);   // 调用 print(int)
        print(5.0); // 调用 print(double)
        return 0;
    }
   ```

2. **模板**：
   模板允许你定义泛型函数或类，这些函数或类可以处理不同类型的数据。

   ```cpp
   template <typename T>
   void print(T value) {
       std::cout << "Print: " << value << std::endl;
   }

   int main() {
       print(5);          // 调用 print<int>(5)
       print(5.0);        // 调用 print<double>(5.0)
       print("Hello");    // 调用 print<std::string>("Hello")
       return 0;
   }
   ```

### 3.2.Run-time Polymorphism (动态多态性)

运行时多态性主要通过虚函数（Virtual Functions）实现。

1. **虚函数**：
   在基类中声明虚函数，并在派生类中重写这些虚函数。

   ```cpp
   #include <iostream>
   
   class Animal {
   public:
       virtual void speak() const {
           std::cout << "Animal makes a sound" << std::endl;
       }
       virtual ~Animal() {} // 虚析构函数确保派生类对象的正确清理
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
       Animal* myAnimal = new Dog();
       myAnimal->speak(); // 输出 "Dog barks"

       Animal* anotherAnimal = new Cat();
       anotherAnimal->speak(); // 输出 "Cat meows"

       delete myAnimal;
       delete anotherAnimal;
       return 0;
   }
   ```

   在这个例子中，`Animal` 是一个基类，它有一个虚函数 `speak()`。`Dog` 和 `Cat` 是派生自 `Animal` 的类，它们重写了 `speak()` 函数。通过基类指针调用 `speak()` 函数时，会根据对象的实际类型调用相应的函数，这就是动态多态性。

2. **抽象类**：
   包含至少一个纯虚函数的类称为抽象类。纯虚函数没有实现，派生类必须提供这些函数的实现。

   ```cpp
   class Shape {
   public:
       virtual void draw() const = 0; // 纯虚函数
       virtual ~Shape() {}
   };

   class Circle : public Shape {
   public:
       void draw() const override {
           std::cout << "Drawing a circle" << std::endl;
       }
   };

   class Rectangle : public Shape {
   public:
       void draw() const override {
           std::cout << "Drawing a rectangle" << std::endl;
       }
   };

   int main() {
       Shape* shape1 = new Circle();
       shape1->draw(); // 输出 "Drawing a circle"

       Shape* shape2 = new Rectangle();
       shape2->draw(); // 输出 "Drawing a rectangle"

       delete shape1;
       delete shape2;
       return 0;
   }
   ```

   在这个例子中，`Shape` 是一个抽象类，它有一个纯虚函数 `draw()`。`Circle` 和 `Rectangle` 是派生自 `Shape` 的类，它们提供了 `draw()` 函数的实现。

通过这些机制，C++ 允许程序员编写更灵活和可扩展的代码。

## 4.如何使用 C++ 的抽象类和纯虚函数来设计一个通用的图形库？

在 C++ 中，使用抽象类和纯虚函数来设计一个通用的图形库是一种常见的做法。这种方法允许你定义一个通用的接口，而具体的实现则由派生类提供。以下是一个简单的例子，展示了如何设计一个基础的图形库：

### 4.1.定义抽象基类 `Shape`

首先，我们定义一个名为 `Shape` 的抽象基类，它包含一个纯虚函数 `draw()`，以及一个虚函数 `area()` 用于计算面积，它在基类中也有一个默认实现。

```cpp
class Shape {
public:
    // 纯虚函数，用于绘制图形
    virtual void draw() const = 0;

    // 虚函数，用于计算图形的面积
    virtual double area() const {
        return 0.0; // 默认实现，对于不关心面积的图形可以返回0
    }

    // 虚析构函数，确保派生类的析构函数被正确调用
    virtual ~Shape() {}
};
```

### 4.2.定义具体的图形类

接下来，我们定义一些具体的图形类，如 `Circle`、`Rectangle` 和 `Triangle`，它们都继承自 `Shape` 类，并实现 `draw()` 函数和 `area()` 函数。

```cpp
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    void draw() const override {
        std::cout << "Drawing a circle with radius: " << radius << std::endl;
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing a rectangle with width: " << width << " and height: " << height << std::endl;
    }

    double area() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    void draw() const override {
        std::cout << "Drawing a triangle with base: " << base << " and height: " << height << std::endl;
    }

    double area() const override {
        return 0.5 * base * height;
    }
};
```

### 4.3.使用图形库

最后，我们可以使用这些图形类来创建一个图形库的客户端代码。

```cpp
int main() {
    // 创建一个 Shape 类型的指针数组
    const int numShapes = 3;
    Shape* shapes[numShapes];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 5.0);
    shapes[2] = new Triangle(3.0, 4.0);

    // 绘制所有图形
    for (int i = 0; i < numShapes; ++i) {
        shapes[i]->draw();
        std::cout << "Area: " << shapes[i]->area() << std::endl;
    }

    // 清理资源
    for (int i = 0; i < numShapes; ++i) {
        delete shapes[i];
    }

    return 0;
}
```

在这个例子中，我们创建了一个 `Shape` 类型的指针数组，然后创建了 `Circle`、`Rectangle` 和 `Triangle` 对象，并将它们存储在数组中。我们遍历数组，调用每个图形的 `draw()` 方法来绘制它们，并计算它们的面积。

这个设计允许我们轻松地添加更多类型的图形，只需确保每个新图形类都继承自 `Shape` 并实现了 `draw()` 和 `area()` 方法。这就是多态性的力量，它允许我们将图形对象统一处理，而不需要知道它们的具体类型。

## 5.在C++中，如何正确地使用虚函数和纯虚函数？

在 C++ 中，虚函数和纯虚函数是实现多态性的关键工具。以下是如何正确使用它们的方法：

### 5.1.虚函数（Virtual Functions）

1. **声明**：在基类中声明一个函数为虚函数，使用 `virtual` 关键字。

   ```cpp
   class Base {
   public:
       virtual void function() {
           // 基类的实现
       }
   };
   ```

2. **实现**：在基类中提供虚函数的实现（可选），或者在派生类中提供。

   ```cpp
   class Derived : public Base {
   public:
       void function() override {
           // 派生类的实现
       }
   };
   ```

3. **覆盖**：在派生类中覆盖基类的虚函数，使用 `override` 关键字（C++11 及以上）。

   ```cpp
   class Derived : public Base {
   public:
       void function() override {
           // 派生类的实现
       }
   };
   ```

4. **调用**：通过基类指针或引用调用虚函数，将根据对象的实际类型动态绑定到相应的函数。

   ```cpp
   Base* b = new Derived();
   b->function(); // 调用 Derived::function()
   delete b;
   ```

### 5.2.纯虚函数（Pure Virtual Functions）

1. **声明**：在基类中声明一个纯虚函数，使用 `= 0`。

   ```cpp
   class Base {
   public:
       virtual void pureFunction() = 0;
   };
   ```

2. **含义**：包含纯虚函数的类称为抽象类，不能实例化。

3. **实现**：派生类必须提供纯虚函数的实现。

   ```cpp
   class Derived : public Base {
   public:
       void pureFunction() override {
           // 实现纯虚函数
       }
   };
   ```

4. **抽象类**：通常用于定义接口和提供默认实现。

   ```cpp
   class Base {
   public:
       virtual void interfaceFunction() = 0;
       virtual void defaultFunction() {
           // 默认实现
       }
   };
   ```

### 5.3.最佳实践

1. **使用 `override`**：总是使用 `override` 关键字来覆盖虚函数，这有助于编译器检查错误。

2. **虚析构函数**：在基类中使用虚析构函数，以确保删除基类指针时能调用正确的析构函数。

   ```cpp
   class Base {
   public:
       virtual ~Base() {}
   };
   ```

3. **避免虚函数的默认参数**：不要为虚函数提供默认参数，因为这可能导致派生类覆盖虚函数时参数不匹配。

4. **小心虚函数的循环依赖**：避免在类之间创建虚函数的循环调用，这可能导致不确定的行为。

5. **合理使用纯虚函数**：纯虚函数应该用于定义接口，而不是提供实际的逻辑。

6. **考虑线程安全**：如果虚函数在多线程环境中被调用，确保它们的实现是线程安全的。

通过正确使用虚函数和纯虚函数，你可以在 C++ 中实现强大的多态性，这使得代码更加灵活和可扩展。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
