# 设计模式-生成器模式 builder_pattern

[TOC]

## Overview

- 生成器模式（Builder Pattern）是一种创建型设计模式
- 用于构造一个复杂的对象。这个对象的构建过程涉及多个步骤，并且希望将构建过程与表示对象本身分离，使得相同的构建过程能够创建出不同的表示。
  - 一个指挥者（Director）对象来控制构建过程
  - 一个产品（Product）接口表示要构建的复杂对象
  - 一个或多个具体的构建者（Builder）类来实现构建过程。

---

## 1.生成器模式 builder_pattern

生成器模式（Builder Pattern）是一种创建型设计模式，用于构造一个复杂的对象。这个对象的构建过程涉及多个步骤，并且希望将构建过程与表示对象本身分离，使得相同的构建过程能够创建出不同的表示。

生成器模式通过引入一个指挥者（Director）对象来控制构建过程，一个产品（Product）接口表示要构建的复杂对象，以及一个或多个具体的构建者（Builder）类来实现构建过程。这样，你可以在不改变构建过程的情况下，通过改变构建者的具体实现来创建不同的产品。

以下是使用C++实现生成器模式的一个示例：

首先，定义产品接口：

```cpp
// Product.h
class Product {
public:
    virtual ~Product() {}
    // 其他产品相关的接口和实现...
};
```

接着，创建具体的产品类：

```cpp
// ConcreteProduct.h
#include "Product.h"

class ConcreteProduct : public Product {
public:
    // 具体产品的实现...
};
```

然后，定义构建者接口：

```cpp
// Builder.h
#include "Product.h"

class Builder {
public:
    virtual ~Builder() {}
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    // 其他构建方法...
    virtual Product* GetProduct() = 0;
};
```

接下来，创建具体的构建者类：

```cpp
// ConcreteBuilder.h
#include "Builder.h"
#include "ConcreteProduct.h"

class ConcreteBuilder : public Builder {
    ConcreteProduct* product_;

public:
    ConcreteBuilder() : product_(new ConcreteProduct()) {}
    ~ConcreteBuilder() {}

    void BuildPartA() override {
        // 构建产品的一部分...
    }

    void BuildPartB() override {
        // 构建产品的一部分...
    }

    Product* GetProduct() override {
        return product_;
    }
};
```

然后，定义指挥者类：

```cpp
// Director.h
#include "Builder.h"

class Director {
public:
    void Construct(Builder* builder) {
        builder->BuildPartA();
        builder->BuildPartB();
        // 调用其他构建方法...
    }
};
```

最后，客户端代码使用生成器模式：

```cpp
// main.cpp
#include "Director.h"
#include "ConcreteBuilder.h"

int main() {
    Director director;
    ConcreteBuilder builder;

    director.Construct(&builder);

    Product* product = builder.GetProduct();
    // 使用构建好的产品...

    delete product; // 清理资源

    return 0;
}
```

在这个示例中，`Product` 是产品接口，`ConcreteProduct` 是具体产品。`Builder` 是构建者接口，`ConcreteBuilder` 是具体构建者，实现了构建过程。`Director` 是指挥者，负责调用构建者的方法来构建产品。客户端代码通过指挥者和构建者来创建复杂的产品对象，而不需要知道具体的构建细节。这样，如果需要添加新的产品类型，只需要添加相应的具体构建者即可，不需要修改现有代码。

## 2.生成器模式优缺点

### 2.1.优点

- 你可以分步创建对象， 暂缓创建步骤或递归运行创建步骤。
- 生成不同形式的产品时， 你可以复用相同的制造代码。
- 单一职责原则。 你可以将复杂构造代码从产品的业务逻辑中分离出来。
  
### 2.2.缺点

- 由于该模式需要新增多个类， 因此代码整体复杂程度会有所增加。

## 3.生成器模式在实际开发中有哪些应用场景？

生成器模式（Builder Pattern）在实际开发中有多种应用场景，尤其适用于创建一个复杂对象的步骤很多，或者对象的创建过程需要高度的灵活性时。以下是一些具体的应用实例：

1. **构建复杂对象**：
   - 当对象的构造需要多个步骤，并且这些步骤可能会经常变化时，使用生成器模式可以将构建过程封装起来，便于管理和修改。

2. **GUI组件构建**：
   - 在图形用户界面（GUI）编程中，生成器模式可以用来构建复杂的界面组件，如面板、菜单、工具栏等，这些组件可能由多个小部件组成。

3. **数据库连接**：
   - 在数据库编程中，可以使用生成器模式构建数据库连接字符串，不同的数据库类型（如MySQL、PostgreSQL）可能需要不同的连接参数。

4. **配置文件解析**：
   - 当需要从配置文件（如XML、JSON）构建配置对象时，生成器模式可以提供一种灵活的方式来处理不同的配置选项。

5. **Web页面内容生成**：
   - 在Web开发中，生成器模式可以用来构建复杂的页面内容，如HTML、CSS、JavaScript代码，这些代码可能由多个部分组成。

6. **报表生成**：
   - 报表软件中，生成器模式可以用来构建复杂的报表，报表可能包含文本、图表、表格等多种元素。

7. **数据结构的构建**：
   - 在算法实现中，如果需要构建复杂的数据结构，如树、图等，生成器模式可以提供一种清晰的方式来组织构建过程。

8. **对象的版本控制**：
   - 当对象有多个版本或变体时，可以使用不同的构建者来创建对象的不同版本。

9. **API请求构建**：
   - 在网络编程中，生成器模式可以用来构建复杂的API请求，包括设置请求头、请求体、参数等。

10. **游戏角色创建**：
    - 在游戏开发中，生成器模式可以用来创建具有多种属性和技能的游戏角色。

11. **汽车配置**：
    - 在实际的汽车制造系统中，生成器模式可以用来根据不同的配置选项构建汽车，如发动机类型、颜色、内饰等。

12. **产品定制**：
    - 对于需要定制的产品，如家具、电脑硬件等，生成器模式可以帮助用户选择不同的组件和选项来定制产品。

使用生成器模式可以使得构建过程与表示对象本身分离，提高系统的灵活性和可扩展性。同时，它也使得相同的构建过程能够创建出不同的表示，增加了代码的复用性。

## 4.生成器模式和工厂模式有什么区别，它们各自适用于什么情况？

生成器模式（Builder Pattern）和工厂模式（Factory Pattern）都是创建型设计模式，用于创建对象，但它们在应用场景和设计意图上存在一些关键的区别：

### 4.1.生成器模式（Builder Pattern）

- **适用场景**：生成器模式适用于创建一个复杂对象，这个对象的构建过程涉及多个步骤，并且希望将构建过程与表示对象本身分离，使得相同的构建过程能够创建出不同的表示。
- **特点**：
  - 创建的对象通常由多个部分组成，且这些部分的构建顺序很重要。
  - 允许用户通过指定的构建步骤来创建一个复杂的对象。
  - 可以存在多个不同的构建者，它们实现了相同的构建接口，但构建过程的细节可能不同。

### 4.2.工厂模式（Factory Pattern）

- **适用场景**：工厂模式用于创建一个对象，当这个对象的创建逻辑与使用该对象的客户端逻辑分离时，可以使用工厂模式。它适用于当创建对象的逻辑较为简单，不需要多个步骤时。
- **特点**：
  - 提供一个接口用于创建对象，让子类决定实例化哪一个类。
  - 通常用于处理对象的创建，这些对象的创建过程不会太复杂。
  - 隐藏了实例创建的细节，由工厂类来决定如何创建对象。

### 4.3.区别

1. **复杂性**：
   - 生成器模式适合创建过程复杂的对象，而工厂模式适合创建过程简单的对象。

2. **分离度**：
   - 生成器模式通过构建者类和指挥者类进一步分离了创建逻辑和表示细节，而工厂模式通常只包含一个工厂类来处理创建逻辑。

3. **灵活性**：
   - 生成器模式提供了更高的灵活性，可以通过不同的构建者类创建不同的产品，而工厂模式通常只能创建一种类型的对象。

4. **使用场景**：
   - 如果对象的创建涉及到多个步骤，并且这些步骤可能会变化，生成器模式是一个更好的选择。
   - 如果对象的创建逻辑相对简单，或者创建逻辑是固定的，工厂模式可能更合适。

5. **可扩展性**：
   - 生成器模式更容易扩展以支持新的产品类型，因为可以引入新的构建者类而不需要修改现有的构建过程。

6. **代码结构**：
   - 生成器模式通常包含多个类（产品、构建者接口、具体构建者、指挥者），而工厂模式可能只包含一个工厂类和产品类。

在选择使用哪种模式时，需要根据实际的需求和上下文来决定。如果对象的创建过程复杂且可能变化，生成器模式提供了更好的解决方案；如果对象的创建过程简单且不太可能变化，工厂模式可能是一个更简单直接的选择。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />