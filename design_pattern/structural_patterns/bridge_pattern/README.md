# 设计模式-桥接模式-bridge pattern

[TOC]

## Overview

- 桥接模式（Bridge Pattern）是一种结构性设计模式
- 用于将抽象部分与其实现部分分离，使它们可以独立地变化
- 通俗来说，桥接模式就是车上船，车就是具体实现

---

## 1.桥接模式（Bridge Pattern）

桥接模式（Bridge Pattern）是一种结构性设计模式，用于将抽象部分与其实现部分分离，使它们可以独立地变化。这种模式通过定义一个桥接接口，将实现的类和抽象的类解耦，从而能够独立地扩展抽象类和实现类。

### 1.1.桥接模式的主要角色包括

1. **抽象（Abstraction）**：
   - 定义了客户使用的接口，维护一个指向实现化对象的引用。

2. **扩展抽象（Refined Abstraction）**：
   - 扩展抽象类，添加了更多的业务方法。

3. **实现化（Implementor）**：
   - 定义了实现化的接口，它不被抽象类直接使用，而是仅作为扩展抽象类的一部分。

4. **具体实现化（Concrete Implementor）**：
   - 实现化接口的具体类，包含了实现化的具体业务。

### 1.2.C++实现示例

首先，定义实现化接口：

```cpp
// Implementor.h
class Implementor {
public:
    virtual ~Implementor() {}
    virtual void operation() = 0;
};
```

接着，创建具体的实现化类：

```cpp
// ConcreteImplementor.h
#include "Implementor.h"

class ConcreteImplementor : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementor operation" << std::endl;
    }
};
```

然后，定义抽象类：

```cpp
// Abstraction.h
#include "Implementor.h"

class Abstraction {
protected:
    Implementor* implementor;

public:
    Abstraction(Implementor* imp) : implementor(imp) {}
    virtual ~Abstraction() {}
    virtual void request() = 0;
};
```

接着，扩展抽象类：

```cpp
// RefinedAbstraction.h
#include "Abstraction.h"

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor* imp) : Abstraction(imp) {}

    void request() override {
        implementor->operation();
        refinedRequest();
    }

    void refinedRequest() {
        std::cout << "Refined request" << std::endl;
    }
};
```

最后，客户端代码使用桥接模式：

```cpp
// main.cpp
#include "ConcreteImplementor.h"
#include "RefinedAbstraction.h"

int main() {
    Implementor* imp = new ConcreteImplementor();
    Abstraction* abstraction = new RefinedAbstraction(imp);

    abstraction->request();

    delete abstraction;
    delete imp;

    return 0;
}
```

### 1.3.桥接模式的应用场景

1. **当一个类存在两个独立变化的维度时**：
   - 例如，一个图形系统，图形的类型和颜色是两个独立变化的维度。

2. **当一个类需要从多个角度进行扩展时**：
   - 每个角度可以使用不同的实现化。

3. **当需要通过第三方类扩展系统时**：
   - 第三方类可以作为实现化部分，而系统的核心功能作为抽象部分。

4. **当不希望使用继承来扩展系统时**：
   - 使用组合和接口来扩展系统，避免继承带来的耦合和限制。

桥接模式提供了一种灵活的方式来扩展系统的功能，同时保持系统的可维护性和可扩展性。通过桥接模式，可以在不修改现有代码的前提下，通过增加新的实现化类来扩展系统。

## 2.桥接模式优缺点

- 优点
  - 你可以创建与平台无关的类和程序。
  - 客户端代码仅与高层抽象部分进行互动， 不会接触到平台的详细信息。
  - 开闭原则。 你可以新增抽象部分和实现部分， 且它们之间不会相互影响。
  - 单一职责原则。 抽象部分专注于处理高层逻辑， 实现部分处理平台细节。
- 缺点
  - 对高内聚的类使用该模式可能会让代码更加复杂。

## 3.桥接模式使用场景

在实际项目中，桥接模式（Bridge Pattern）可以应用于多种场景，尤其是当需要将一个类的抽象部分与它的实现部分分离，以便它们可以独立地变化和扩展时。以下是一些具体的应用实例：

1. **图形界面库开发**：
   - 在开发图形界面库时，可以使用桥接模式将界面的绘制（抽象部分）与具体的控件类型（实现部分）分离。这样，增加新的控件类型或改变绘制方式时，不需要修改已有的代码。

2. **支付系统设计**：
   - 在支付系统中，支付方式（如信用卡、PayPal、微信支付）可以作为实现化角色，而支付接口作为抽象部分。这样，添加新的支付方式或修改现有支付逻辑时互不影响。

3. **游戏角色和行为分离**：
   - 在游戏开发中，角色（如战士、法师）可以有一个抽象类，而具体的行为（如攻击、防御、移动）可以作为实现化角色。这样，可以灵活地为不同角色分配不同的行为。

4. **硬件设备的驱动程序开发**：
   - 当开发硬件设备的驱动程序时，可以使用桥接模式将设备的硬件控制（抽象部分）与具体的操作（实现部分）分离。这样，更换设备或更新操作逻辑时更加灵活。

5. **网络应用的协议处理**：
   - 在网络通信中，可以使用桥接模式将协议的抽象处理与具体的协议实现分离。这样，增加新的协议或修改现有协议的处理逻辑时，不需要修改核心的协议处理代码。

6. **报告生成系统**：
   - 在报告生成系统中，报告的格式（如PDF、Excel、HTML）可以作为实现化角色，而报告的内容生成逻辑作为抽象部分。这样，添加新的报告格式或修改报告内容时互不干扰。

7. **多语言支持**：
   - 在需要多语言支持的应用程序中，可以使用桥接模式将用户界面的元素（抽象部分）与不同的语言资源（实现部分）分离。这样，添加新的语言或更新翻译时更加方便。

8. **软件的插件架构**：
   - 当软件采用插件架构时，可以使用桥接模式将插件的接口（抽象部分）与具体的插件实现（实现部分）分离。这样，开发新的插件或更新现有插件时互不影响。

9. **资源管理器**：
   - 在资源管理器中，可以使用桥接模式将资源的访问方式（抽象部分）与具体的资源类型（实现部分）分离。这样，增加新的资源类型或改变资源访问方式时更加灵活。

通过这些应用实例，我们可以看到桥接模式在实际项目中的价值，它有助于提高代码的可维护性、可扩展性和灵活性。在设计系统时，如果预见到某个类可能会有多个变化维度，考虑使用桥接模式来避免未来代码的复杂性。

## 4.在实际项目中，如何确保桥接模式的实现与抽象部分的解耦？

在实际项目中，确保桥接模式的实现与抽象部分的解耦，可以遵循以下几个关键步骤：

1. **明确角色职责**：
   - 清晰定义抽象部分（Abstraction）和实现部分（Implementor）的职责，确保它们之间的接口是明确的，并且没有依赖关系。

2. **使用接口或抽象类**：
   - 为实现部分定义一个接口或抽象类，这个接口或抽象类将被抽象部分所依赖，而不是具体的实现类。

3. **依赖关系反向**：
   - 确保抽象部分不直接依赖具体实现类，而是依赖实现部分的接口或抽象类。

4. **通过组合实现解耦**：
   - 在抽象部分中，使用一个成员变量来组合实现部分的接口或抽象类，而不是具体实现类。

5. **避免直接引用实现类**：
   - 在抽象部分的代码中，避免直接引用任何实现类的实例，所有的操作都通过实现部分的接口或抽象类来进行。

6. **使用工厂模式**：
   - 可以使用工厂模式来创建实现部分的对象，这样可以进一步解耦实现部分的具体类和抽象部分。

7. **定义清晰的协议**：
   - 为实现部分定义清晰的协议或接口，确保所有实现类都遵循这个协议，这样抽象部分不依赖于任何特定的实现细节。

8. **单一职责原则**：
   - 遵循单一职责原则，确保抽象类和实现类都只处理它们应该处理的职责。

9. **编写单元测试**：
   - 为抽象部分和实现部分编写单元测试，确保它们可以独立于彼此进行测试。

10. **代码审查**：
    - 通过代码审查来确保实现遵循桥接模式的原则，没有不当的依赖关系。

11. **文档和注释**：
    - 编写清晰的文档和注释，说明抽象部分和实现部分的接口和职责。

12. **逐步集成**：
    - 在集成过程中，逐步将抽象部分和实现部分结合起来，确保它们可以协同工作，同时保持各自的独立性。

13. **使用依赖注入**：
    - 利用依赖注入（Dependency Injection）来动态地将实现部分注入到抽象部分中，而不是在抽象部分中创建具体实现的实例。

14. **避免条件语句**：
    - 避免在抽象部分中使用条件语句来判断具体的实现类型，这有助于保持解耦。

通过这些步骤，可以确保在实际项目中实现桥接模式时，抽象部分和实现部分能够保持高度的解耦，从而提高代码的灵活性和可维护性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
