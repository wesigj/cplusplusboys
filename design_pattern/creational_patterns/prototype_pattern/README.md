# 设计模式-原型模式 Prototype Pattern

[TOC]

## Overview

- 原型模式（Prototype Pattern）是一种创建型设计模式
- 它允许你通过复制现有的对象来创建新的实例，而不是通过新建的方式来构造
- 这种模式特别适用于那些创建过程复杂、资源消耗大或者创建后需要快速复制的场景

---

## 1.原型模式 Prototype Pattern

原型模式（Prototype Pattern）是一种创建型设计模式，它允许你通过复制现有的对象来创建新的实例，而不是通过新建的方式来构造。这种模式特别适用于那些创建过程复杂、资源消耗大或者创建后需要快速复制的场景。

### 1.1.原型模式的主要角色包括

1. **原型接口（Prototype Interface）**：
   - 声明一个克隆自己的操作，通常是一个`Clone`方法。

2. **具体原型类（Concrete Prototype）**：
   - 实现原型接口，提供具体的`Clone`方法来返回对象的副本。

3. **客户端（Client）**：
   - 创建和操作具体原型对象，通过调用`Clone`方法来复制对象。

### 1.2.C++实现示例

首先，定义原型接口：

```cpp
// Prototype.h
class Prototype {
public:
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
};
```

接着，创建具体的原型类：

```cpp
// ConcretePrototype.h
#include "Prototype.h"

class ConcretePrototype : public Prototype {
private:
    std::string value;

public:
    ConcretePrototype(const std::string& val) : value(val) {}
    ConcretePrototype(const ConcretePrototype& other) : value(other.value) {}

    Prototype* Clone() const override {
        return new ConcretePrototype(*this);
    }

    // 其他方法...
};
```

然后，客户端代码使用原型模式：

```cpp
// main.cpp
#include "ConcretePrototype.h"

int main() {
    ConcretePrototype* original = new ConcretePrototype("Original Object");
    
    // 复制对象
    ConcretePrototype* copy = original->Clone();

    // 使用复制的对象...
    // ...

    delete original; // 清理原始对象
    delete copy;     // 清理复制的对象

    return 0;
}
```

### 1.3.原型模式的应用场景

1. **创建成本高**：
   - 当对象的构造成本很高时，使用原型模式可以通过复制现有对象来降低创建成本。

2. **创建过程复杂**：
   - 如果创建对象的过程非常复杂，涉及多个步骤或者依赖多个外部条件，使用原型模式可以简化创建过程。

3. **对象的初始状态是固定的**：
   - 当需要创建的对象具有固定的初始状态，并且后续需要在此基础上进行修改时，原型模式可以快速提供初始状态。

4. **对象状态容易改变**：
   - 如果对象的状态容易改变，并且需要保存和恢复状态，原型模式可以方便地保存对象的状态快照。

5. **实现对象的动态加载和卸载**：
   - 在需要根据需求动态加载和卸载对象的场景下，原型模式可以快速复制对象，实现对象的动态管理。

6. **实现对象的版本控制**：
   - 当对象有多个版本，并且需要在不同版本之间切换时，原型模式可以方便地复制和维护不同版本的实例。

### 1.4.注意事项

- 原型模式要求所有克隆的对象都是可复制的，这可能会限制对象所包含的成员类型（如不能包含指针或引用类型的成员）。
- 深拷贝和浅拷贝：默认情况下，C++的拷贝构造函数执行的是浅拷贝。如果对象包含指针等需要特殊处理的成员，可能需要实现深拷贝逻辑。
- 使用原型模式可能会增加内存的消耗，因为需要存储多个对象副本。

## 2.原型模式优缺点

### 2.1.优点

- 你可以克隆对象， 而无需与它们所属的具体类相耦合。
- 你可以克隆预生成原型， 避免反复运行初始化代码。
- 你可以更方便地生成复杂对象。
- 你可以用继承以外的方式来处理复杂对象的不同配置。

### 2.2.缺点

- 克隆包含循环引用的复杂对象可能会非常麻烦。

## 3.原型模式在实际开发中有哪些常见的应用场景？

原型模式（Prototype Pattern）在实际开发中有许多应用场景，尤其适用于需要快速复制或克隆对象的情况。以下是一些常见的应用实例：

1. **配置信息的复制**：
   - 在应用程序中，如果存在多个配置实例，它们之间只有少量差异，可以使用原型模式快速复制一个基础配置，然后进行少量修改。

2. **UI元素的复制**：
   - 在图形界面开发中，如果需要创建多个相似的控件或组件，可以使用原型模式复制一个已有的控件，然后进行个性化调整。

3. **对象的快速加载**：
   - 当对象的创建过程非常耗时或占用大量资源时，可以使用原型模式预先创建好对象，然后通过复制来快速提供对象实例。

4. **数据备份**：
   - 在需要对数据进行备份的场景中，可以使用原型模式来复制对象，快速生成数据的副本。

5. **游戏开发中的角色克隆**：
   - 在游戏开发中，如果存在多个相似的角色或敌人，可以使用原型模式来复制一个基础角色，然后根据需要进行调整。

6. **Web开发中的页面元素复制**：
   - 在Web开发中，如果需要在页面上复制多个相似的DOM元素，可以使用原型模式的思想来实现。

7. **报表工具中的数据系列复制**：
   - 在报表工具中，如果用户需要复制一个数据系列并对其进行修改，可以使用原型模式快速复制数据系列。

8. **办公软件中的文档模板**：
   - 在办公软件中，如果提供了多种文档模板，用户可以复制一个模板来创建新文档，然后进行个性化编辑。

9. **数据库中的记录复制**：
   - 在数据库应用中，如果需要复制具有相似属性的记录，可以使用原型模式快速复制记录。

10. **实现对象的版本控制**：
    - 在需要对对象进行版本控制的场景中，可以使用原型模式来复制对象的不同版本。

11. **实现对象的深克隆**：
    - 当对象需要进行深克隆，即完全复制包括对象内部所有引用对象的副本时，可以使用原型模式。

12. **实现对象的池模式**：
    - 在对象池模式中，可以使用原型模式来快速复制对象，实现对象的复用。

13. **实现软件的插件架构**：
    - 在插件架构中，可以使用原型模式来复制插件实例，以支持多个插件的相同行为。

14. **实现算法的参数设置**：
    - 在算法实现中，如果算法参数对象较为复杂，可以使用原型模式复制参数对象，方便算法的多次调用。

使用原型模式可以提高对象创建的效率，降低系统的资源消耗，并有助于实现对象的快速复制和灵活管理。然而，需要注意的是，原型模式可能会增加内存消耗，并且在处理包含引用类型成员的对象时需要特别小心，以避免浅拷贝导致的问题。

## 4.在实际开发中，如何决定何时使用原型模式而不是其他模式，比如单例模式？

在实际开发中，选择使用原型模式（Prototype Pattern）而不是其他模式，如单例模式（Singleton Pattern），取决于具体的应用场景和设计需求。以下是一些考虑因素，可以帮助你决定何时使用原型模式：

1. **对象创建的复杂性**：
   - 如果对象的创建过程非常复杂或资源消耗大，原型模式可以通过复制现有对象来简化创建过程。单例模式则用于确保一个类只有一个实例，并提供一个全局访问点。

2. **对象的可变性**：
   - 如果对象的状态或属性需要频繁变化，并且这些变化不会影响到其他对象，原型模式可以提供灵活性，允许快速复制并修改对象。而单例模式通常用于提供不变且唯一的实例。

3. **对象的多样性**：
   - 当需要创建多个相似但又不完全相同的对象时，原型模式可以通过复制一个基础对象并进行小的调整来实现。单例模式不适用于需要多个实例的情况。

4. **性能考虑**：
   - 如果对象创建的性能是关键考虑因素，原型模式可以提供快速的对象创建。单例模式在首次创建实例时可能需要一些初始化工作，但之后提供全局访问点的速度很快。

5. **对象的共享性**：
   - 单例模式的核心是提供一个全局访问点，确保所有访问都使用相同的实例。如果需要的对象是可变的，并且需要在不同地方共享相同的状态，单例模式可能更合适。

6. **对象的独立性**：
   - 如果需要的对象是独立的，并且不需要与其他对象共享状态，原型模式可以提供这种独立性。单例模式则强调共享同一实例。

7. **对象的配置**：
   - 如果对象需要根据不同的配置创建多个变体，原型模式可以方便地复制一个基础配置并进行调整。单例模式通常不适用于需要多个配置实例的情况。

8. **对象的生命周期**：
   - 单例模式的对象通常在应用程序的整个生命周期内都存在。如果对象的生命周期需要更加灵活，例如需要根据需求创建和销毁，原型模式可能更合适。

9. **线程安全**：
   - 单例模式需要考虑线程安全问题，确保在多线程环境中只创建一个实例。原型模式在复制对象时也需要考虑线程安全，尤其是在对象包含可变共享资源时。

10. **设计意图**：
    - 考虑设计模式的设计意图。单例模式的意图是控制实例数量，而原型模式的意图是通过复制来创建新实例。

11. **可扩展性**：
    - 如果系统未来可能需要支持更多类型的实例，原型模式提供了更好的可扩展性，允许通过继承和组合来创建新的对象类型。

12. **资源管理**：
    - 如果对象包含需要特殊管理的资源，如文件句柄或数据库连接，单例模式可以确保这些资源被适当地管理和重用。原型模式则需要确保复制的对象不会共享这些资源，除非这是预期的行为。

在决定使用原型模式还是单例模式时，需要根据实际的需求和上下文来权衡。通常，如果需要快速复制对象并且对象的创建成本较高，或者需要创建多个相似但不完全相同的对象，原型模式是一个更好的选择。如果目标是控制实例的数量并提供一个全局访问点，单例模式可能更合适。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />