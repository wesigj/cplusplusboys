# 设计模式-工厂方法模式

[TOC]

## Overview

- **工厂方法模式是一种创建型设计模式**
- **子类继承，重载，多态基类**
- **具体工厂生产具体产品**
- **看起来内容挺多的，要耐心啊！**

---

工厂方法模式（Factory Method Pattern）是一种创建型设计模式，用于将对象的创建过程封装在一个函数或方法中，从而将对象的创建和使用分离。这种模式允许系统在不修改已有代码的情况下引入新的产品。

## 1.工厂方法模式简介

### 1.1. 工厂方法模式的关键特点

1. **封装性**：对象的创建过程被封装在一个函数或方法中。
2. **扩展性**：当需要添加新的产品时，只需添加相应的具体产品类和相应的具体工厂类，无需修改已有代码。
3. **解耦**：客户端代码独立于具体产品类，只与抽象产品和工厂类交互。

### 1.2. 工厂方法模式的结构

- **产品（Product）**：定义了产品的接口。
- **具体产品（Concrete Product）**：实现了产品接口的具体类。
- **工厂（Factory）**：定义了创建产品的方法，通常是一个静态方法或抽象方法。
- **具体工厂（Concrete Factory）**：实现了工厂接口，生成具体产品对象。

### 1.3. C++ 示例代码

```cpp
#include <iostream>

// 产品接口
class Product {
public:
    virtual ~Product() {}
    virtual void use() = 0;
};

// 具体产品
class ConcreteProduct : public Product {
public:
    void use() override {
        std::cout << "Using ConcreteProduct" << std::endl;
    }
};

// 工厂接口
class Factory {
public:
    virtual ~Factory() {}
    virtual Product* createProduct() = 0;
};

// 具体工厂
class ConcreteFactory : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProduct();
    }
};

// 客户端代码
int main() {
    Factory* factory = new ConcreteFactory();
    Product* product = factory->createProduct();
    product->use(); // 使用具体产品
    delete product; // 释放资源
    delete factory; // 释放资源
    return 0;
}
```

### 1.4. 注意事项

- **简单工厂**：如果创建逻辑简单，可以使用简单工厂模式，将所有创建逻辑放在一个工厂类中。
- **参数化工厂**：如果创建对象需要外部参数，可以在工厂方法中传递这些参数。
- **工厂方法模式与抽象工厂模式**：工厂方法模式用于创建单一产品，而抽象工厂模式用于创建产品族。
- **性能考虑**：工厂方法模式可能会引入额外的性能开销，尤其是在创建对象时。

工厂方法模式适用于当创建对象的逻辑复杂或者需要将创建逻辑与使用逻辑分离的场景。它提高了系统的灵活性和扩展性，使得在不修改现有代码的情况下引入新的产品变得更加容易。

## 2.如何用工厂方法模式解决代码中的耦合问题？

工厂方法模式通过将对象的创建逻辑从使用对象的代码中分离出来，可以有效地解决代码耦合问题。以下是使用工厂方法模式解决耦合问题的步骤和示例：

### 2.1. 步骤

1. **定义产品接口**：为需要解耦的对象创建一个接口或抽象类。

2. **实现具体产品**：为每种具体的对象类型实现产品接口。

3. **定义工厂接口**：为创建产品定义一个工厂接口或抽象类。

4. **实现具体工厂**：为每种具体产品类型实现一个具体的工厂类。

5. **客户端使用工厂**：客户端代码通过工厂接口请求产品，而不是直接创建具体产品。

6. **解耦客户端和具体实现**：客户端不再依赖于具体产品类的实现，只依赖于产品接口和工厂接口。

### 2.2. 示例

假设我们有一个应用程序，它使用不同类型的日志记录器，但我们希望客户端代码不依赖于具体的日志记录器实现。

#### 2.2.1. 定义日志记录器接口

```cpp
class Logger {
public:
    virtual ~Logger() {}
    virtual void log(const std::string& message) = 0;
};
```

#### 2.2.2. 实现具体日志记录器

```cpp
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Console: " << message << std::endl;
    }
};

class FileLogger : public Logger {
public:
    void log(const std::string& message) override {
        // 将日志消息写入文件
    }
};
```

#### 2.2.3. 定义工厂接口

```cpp
class LoggerFactory {
public:
    virtual ~LoggerFactory() {}
    virtual Logger* createLogger() = 0;
};
```

#### 2.2.4. 实现具体工厂

```cpp
class ConsoleLoggerFactory : public LoggerFactory {
public:
    Logger* createLogger() override {
        return new ConsoleLogger();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    Logger* createLogger() override {
        return new FileLogger();
    }
};
```

#### 2.2.5. 客户端使用工厂

```cpp
class Application {
private:
    LoggerFactory* loggerFactory;

public:
    Application(LoggerFactory* factory) : loggerFactory(factory) {}

    void setLoggerFactory(LoggerFactory* factory) {
        loggerFactory = factory;
    }

    void log(const std::string& message) {
        Logger* logger = loggerFactory->createLogger();
        logger->log(message);
        delete logger; // 使用完毕后释放资源
    }
};

int main() {
    Application app;

    // 根据配置或环境设置不同的日志记录器
    std::string loggerType;
    std::cout << "Enter logger type (Console/File): ";
    std::cin >> loggerType;

    if (loggerType == "Console") {
        app.setLoggerFactory(new ConsoleLoggerFactory());
    } else if (loggerType == "File") {
        app.setLoggerFactory(new FileLoggerFactory());
    } else {
        std::cerr << "Invalid logger type" << std::endl;
        return 1;
    }

    app.log("This is a log message.");

    return 0;
}
```

### 2.3. 解耦的优势

- **易于扩展**：添加新的日志记录器类型时，只需添加新的具体日志记录器类和相应的工厂类。
- **提高模块化**：客户端代码与日志记录器的具体实现解耦，只依赖于接口。
- **灵活配置**：可以在运行时根据配置选择不同的日志记录器，无需修改客户端代码。

通过这种方式，工厂方法模式使得代码更加灵活和可维护，同时降低了各组件之间的依赖性。

## 3.应用场景

工厂方法模式在实际开发中有多种应用场景，以下是一些常见的例子：

1. **数据库连接**：
   创建不同类型的数据库连接（如 MySQL、PostgreSQL）时，可以使用工厂方法模式根据不同的数据库类型生成相应的数据库连接对象。

2. **图形用户界面（GUI）组件**：
   在GUI应用程序中，创建不同类型的按钮、文本框等组件时，可以使用工厂方法模式来封装组件的创建过程。

3. **日志记录器**：
   根据不同的日志级别或日志输出目的地（如控制台、文件、网络）创建不同的日志记录器实例。

4. **配置文件解析器**：
   针对不同的配置文件格式（如 XML、JSON、YAML）创建相应的解析器对象。

5. **支付网关集成**：
   在电子商务应用中，根据不同的支付服务提供商（如 PayPal、Stripe、Alipay）创建支付网关实例。

6. **对象-关系映射（ORM）**：
   在ORM框架中，根据数据库表映射创建相应的模型对象。

7. **图像处理**：
   根据不同的图像格式（如 JPEG、PNG、GIF）创建相应的图像处理对象。

8. **协议处理器**：
   在网络编程中，根据不同的通信协议（如 HTTP、FTP、SMTP）创建对应的协议处理器对象。

9. **报表生成**：
   根据不同的报表格式（如 PDF、Excel、HTML）创建相应的报表生成器。

10. **邮件发送**：
    根据邮件发送服务（如 SMTP、SendGrid、Amazon SES）创建邮件发送对象。

11. **硬件设备驱动程序**：
    为不同类型的硬件设备（如打印机、扫描仪）创建相应的驱动程序实例。

12. **API客户端**：
    为不同的API服务（如 Twitter API、Facebook API）创建客户端实例。

13. **依赖注入容器**：
    在依赖注入框架中，工厂方法模式用于创建依赖项的实例。

14. **多态性实现**：
    在需要实现多态性的场景中，工厂方法可以用来根据条件生成继承体系中的特定子类实例。

15. **游戏开发**：
    在游戏开发中，根据不同的敌人类型或游戏对象创建相应的对象实例。

工厂方法模式通过将对象创建的逻辑封装起来，使得代码更加模块化和可维护，同时也提高了扩展性。当系统中存在多种类型的对象需要创建，并且这些对象的创建逻辑可能会变化时，工厂方法模式尤其有用。

## 4.用工厂方法模式实现数据库连接类

当然，以下是一个使用工厂方法模式的具体示例，我们将创建一个简单的数据库连接工厂，用于根据不同的数据库类型生成相应的数据库连接对象。

### 4.1. 假设我们有以下数据库连接类

```cpp
// MySQL数据库连接类
class MySQLConnection {
public:
    void connect() {
        std::cout << "Connecting to MySQL database..." << std::endl;
        // MySQL连接逻辑
    }
};

// PostgreSQL数据库连接类
class PostgreSQLConnection {
public:
    void connect() {
        std::cout << "Connecting to PostgreSQL database..." << std::endl;
        // PostgreSQL连接逻辑
    }
};
```

### 4.2. 定义一个数据库连接的接口

```cpp
class DatabaseConnection {
public:
    virtual ~DatabaseConnection() {}
    virtual void connect() = 0;
};
```

### 4.3. 创建一个工厂基类

```cpp
class DatabaseConnectionFactory {
public:
    virtual ~DatabaseConnectionFactory() {}
    virtual DatabaseConnection* createConnection() = 0;
};
```

### 4.3. 实现具体的工厂类

```cpp
// MySQL数据库连接工厂
class MySQLConnectionFactory : public DatabaseConnectionFactory {
public:
    DatabaseConnection* createConnection() override {
        return new MySQLConnection();
    }
};

// PostgreSQL数据库连接工厂
class PostgreSQLConnectionFactory : public DatabaseConnectionFactory {
public:
    DatabaseConnection* createConnection() override {
        return new PostgreSQLConnection();
    }
};
```

### 4.4. 客户端使用示例

```cpp
int main() {
    // 客户端代码，根据需要选择数据库类型
    std::string dbType;
    std::cout << "Enter database type (MySQL/PostgreSQL): ";
    std::cin >> dbType;

    DatabaseConnectionFactory* factory;
    if (dbType == "MySQL") {
        factory = new MySQLConnectionFactory();
    } else if (dbType == "PostgreSQL") {
        factory = new PostgreSQLConnectionFactory();
    } else {
        std::cerr << "Invalid database type" << std::endl;
        return 1;
    }

    DatabaseConnection* dbConnection = factory->createConnection();
    dbConnection->connect();

    // 释放资源
    delete dbConnection;
    delete factory;

    return 0;
}
```

在这个示例中，我们定义了一个`DatabaseConnection`接口和两个具体的数据库连接类`MySQLConnection`和`PostgreSQLConnection`。然后，我们创建了`DatabaseConnectionFactory`工厂接口和两个具体的工厂类`MySQLConnectionFactory`与`PostgreSQLConnectionFactory`。在`main`函数中，根据用户输入选择相应的数据库类型，并使用相应的工厂来创建和连接数据库。

这个示例展示了工厂方法模式如何帮助我们封装对象创建的复杂性，并且使得系统更容易扩展。如果需要支持新的数据库类型，我们只需添加新的数据库连接类和相应的工厂类，而无需修改现有的代码。

## 5.工厂模式 单元测试

工厂方法模式在实际项目中的单元测试通常涉及以下几个方面：

1. **测试工厂类创建对象的功能**：验证工厂类是否能够根据给定的参数或条件正确创建出预期的对象类型。这通常涉及到检查返回的对象是否是正确的类实例。

2. **测试对象的正确性**：确保通过工厂方法创建的对象具有正确的属性和状态。这可能包括验证对象的字段值、状态或行为是否符合预期。

3. **测试边界条件和异常处理**：检查工厂方法在面对不寻常的输入或错误条件时是否能够妥善处理，例如返回`null`或抛出异常。

4. **测试代码覆盖率**：确保单元测试覆盖了工厂方法的所有分支和逻辑路径，以验证代码的健壮性。

5. **测试解耦合性**：验证工厂方法模式是否成功地将对象创建的逻辑与使用对象的逻辑分离，从而降低代码之间的耦合度。

6. **测试可扩展性**：通过添加新的产品类和相应的工厂类来测试系统是否能够灵活扩展，而无需修改现有代码。

7. **使用模拟对象**：在测试中使用模拟（mock）对象来模拟依赖关系，确保测试的独立性和可重复性。

8. **编写清晰的测试用例**：每个测试用例应该具有明确的目的和描述，便于理解和维护。

9. **执行测试并验证结果**：运行测试并检查结果是否符合预期，确保所有测试都通过。

10. **持续集成**：将单元测试集成到持续集成流程中，确保代码的每次提交都能自动运行测试，及时发现问题。

通过这些测试策略，可以确保工厂方法模式的实现是正确、可靠和易于维护的。单元测试不仅帮助开发者验证代码的正确性，还提高了代码质量和项目的可维护性。

## 6.工厂方法模式和简单工厂模式有什么区别，它们各自适用于什么情况？

工厂方法模式（Factory Method Pattern）和简单工厂模式（Simple Factory Pattern）都是创建型设计模式，它们用于封装对象的创建过程。尽管它们的目的相似，但它们在结构和使用场景上有一些关键的区别：

### 6.1.简单工厂模式

1. **定义**：简单工厂模式使用一个中心工厂类来创建所有类型的对象。这个类负责接收参数并根据参数决定创建哪种类型的对象。
2. **结构**：简单工厂模式通常包含一个工厂类和多个具体产品类。
3. **优点**：
   - 易于理解和实现。
   - 客户端不需要知道具体的类是如何实现的。
   - 隐藏了对象创建的复杂性。
4. **缺点**：
   - 工厂类集中了所有创建逻辑，违反了单一职责原则。
   - 每增加一个产品类别，都需要修改工厂类，违反了开闭原则。
5. **适用场景**：
   - 当创建逻辑比较简单，不需要重复编写创建代码时。
   - 当产品种类较少，且新增产品类别的频率较低时。

### 6.2.工厂方法模式

1. **定义**：工厂方法模式定义了一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法让类的实例化推迟到子类。
2. **结构**：工厂方法模式包含一个抽象工厂接口、多个具体工厂类和多个具体产品类。
3. **优点**：
   - 遵循开闭原则，增加新的产品类不需要修改现有代码。
   - 增加了创建逻辑的扩展性，每个具体工厂类负责创建一种产品。
   - 符合单一职责原则，每个工厂类只负责创建一种具体产品。
4. **缺点**：
   - 增加了系统的复杂度，需要为每个产品类创建对应的工厂类。
   - 增加了系统的抽象性和理解难度。
5. **适用场景**：
   - 当产品类别较多，且需要根据不同的条件创建不同的产品实例时。
   - 当系统需要扩展性，能够灵活地引入新产品类别而不影响现有代码时。

### 6.3.区别

- **扩展性**：工厂方法模式更容易扩展，因为它遵循开闭原则，而简单工厂模式在添加新产品时需要修改工厂类。
- **职责分配**：工厂方法模式将创建逻辑分散到各个具体工厂类中，而简单工厂模式将所有创建逻辑集中在一个工厂类中。
- **抽象程度**：工厂方法模式提供了更高层次的抽象，允许系统在运行时动态选择使用哪个工厂类。

在选择使用哪种模式时，需要根据实际项目的需求、系统的复杂度和预期的扩展性来决定。如果预计产品类别会频繁变化或增加，工厂方法模式可能是更好的选择。如果产品类别相对固定且数量较少，简单工厂模式可能更简单直接。

## 7.在实际开发中，如何决定使用工厂方法模式还是简单工厂模式？

在实际开发中，决定使用工厂方法模式还是简单工厂模式，可以根据以下几个关键因素进行考虑：

1. **扩展性需求**：
   - 如果系统预计会有频繁的产品种类扩展，或者需要在未来添加更多产品类型，工厂方法模式更加合适，因为它遵循开闭原则，易于扩展。

2. **产品种类数量**：
   - 如果系统中的产品种类较少，或者新增产品的需求较低，简单工厂模式可能更加简单和直接。

3. **创建逻辑复杂度**：
   - 如果对象的创建逻辑相对简单，或者创建过程中不需要太多子类特有的逻辑，简单工厂模式可能更合适。
   - 如果对象的创建逻辑较为复杂，或者不同的产品类型需要不同的创建逻辑，工厂方法模式允许将这些逻辑分散到各个具体工厂类中。

4. **系统耦合度**：
   - 如果希望降低系统各部分之间的耦合度，工厂方法模式通过定义抽象工厂接口，使得客户端代码与具体实现解耦。

5. **代码维护性**：
   - 如果系统的可维护性是关键考虑因素，工厂方法模式通常提供更好的维护性，因为它允许在不修改现有代码的基础上引入新的产品类型。

6. **性能考虑**：
   - 如果性能是一个关键因素，并且对象创建不是性能瓶颈，可以选择简单工厂模式，因为它可能更轻量级。
   - 如果对象创建过程可能影响性能，工厂方法模式允许对创建过程进行优化，而不影响其他工厂类。

7. **设计原则遵循**：
   - 如果希望严格遵循设计原则，如单一职责原则和开闭原则，工厂方法模式是更好的选择。

8. **团队熟悉度**：
   - 考虑团队对设计模式的熟悉程度和偏好。如果团队对工厂方法模式更熟悉，选择工厂方法模式可能更有利于项目的顺利进行。

9. **项目规模**：
   - 对于大型项目或企业级应用，工厂方法模式可能更合适，因为它提供了更好的扩展性和灵活性。
   - 对于小型或简单的项目，简单工厂模式可能足够用，且实现起来更快捷。

10. **现有代码基础**：
    - 如果现有系统已经采用了工厂方法模式，新增功能时继续使用工厂方法模式可以保持代码风格的一致性。
    - 如果现有系统较小，且没有使用设计模式，引入简单工厂模式可能更简单。

综合考虑上述因素，可以做出更合适的选择。在一些情况下，两种模式可以结合使用，例如，使用简单工厂模式来处理创建逻辑相对简单的对象，而使用工厂方法模式来处理需要高度扩展性的对象。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
