# 设计模式-创建式模式-creational patterns

[TOC]

## Overview

---

## 1.创建式模式（Creational Patterns）

创建式模式（Creational Patterns）是软件设计模式的一种，主要用于处理对象的创建过程，封装对象的实例化过程，以便更好地控制对象的创建。创建式模式隐藏了对象如何创建、组合和表示的复杂性，而不是直接暴露给客户端代码。以下是五种基本的创建式设计模式：

1. **单例模式（Singleton Pattern）**：
   - 确保一个类只有一个实例，并提供一个全局访问点。

2. **工厂方法模式（Factory Method Pattern）**：
   - 定义一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法让类的实例化推迟到子类进行。

3. **抽象工厂模式（Abstract Factory Pattern）**：
   - 创建相关或依赖对象的家族，而不需明确指定具体类。它提供一个接口，用于创建一系列相关或相互依赖的对象，而不需要指定它们具体的类。

4. **生成器模式（Builder Pattern）**：
   - 用于创建一个复杂对象，同时允许用户只通过指定复杂对象的类型和内容就可以构建它们，用户不需要知道内部的具体构建细节。

5. **原型模式（Prototype Pattern）**：
   - 使用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。

每种创建式模式都有其特定的应用场景和优缺点，以下是它们的一些使用场景：

- **单例模式**：适用于需要全局只有一个实例的情况，如配置管理器、连接池等。
- **工厂方法模式**：适用于需要根据不同条件创建不同实例的情况，如支付接口的实现。
- **抽象工厂模式**：适用于需要创建产品族的情况，这些产品在结构上相关联，如不同操作系统的GUI组件。
- **生成器模式**：适用于需要构建复杂对象，且对象的构建过程涉及多个步骤的情况，如构建一个包含多个部件的汽车。
- **原型模式**：适用于创建新对象的成本较高，或者对象的创建过程需要高度的灵活性时，如图形界面的复制操作。

选择使用哪种创建式模式，需要根据实际的需求和上下文来决定。创建式模式有助于提高代码的可维护性、可读性和灵活性。

- [工厂方法模式 factory_method_mode](./factory_method_mode/README.md)
- [抽象工厂模式 abstract_factory](./abstract_factory/README.md)
- [生成器模式 builder_pattern](./builder_pattern/README.md)
- [原型模式 prototype_pattern](./prototype_pattern/README.md)
- [单例模式 singleton_pattern](./singleton_pattern/README.md)

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
