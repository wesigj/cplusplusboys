# 设计模式-中介者模式-Mediator Pattern

[TOC]

## Overview

- 中介者模式（Mediator Pattern）是一种行为型设计模式
- 它通过引入一个中介者对象来封装一系列的对象交互，使得对象之间不需要显式地相互引用，从而使得其耦合松散，而且可以独立地改变它们之间的交互

---

## 1.中介者模式（Mediator Pattern）

中介者模式（Mediator Pattern）是一种行为型设计模式，它通过引入一个中介者对象来封装一系列的对象交互，使得对象之间不需要显式地相互引用，从而使得其耦合松散，而且可以独立地改变它们之间的交互。这种模式在C++中的实现通常涉及以下几个关键组件：

1. **抽象中介者（Mediator）**：定义了一个接口，该接口提供了同事对象注册和转发同事对象信息的方法。

2. **具体中介者（ConcreteMediator）**：实现中介者接口，协调各个同事角色之间的交互关系。

3. **抽象同事类（Colleague）**：定义同事类的接口，保存中介者对象的引用，并提供同事对象交互的抽象方法。

4. **具体同事类（Concrete Colleague）**：实现抽象同事类，当需要与其他同事对象通信时，通过中介者进行。

在C++中实现中介者模式的一个简单示例如下：

```cpp
#include <iostream>
#include <vector>
#include <memory>

// 抽象中介者
class Mediator {
public:
    virtual void Send(const std::string& message, Colleague* colleague) = 0;
};

// 具体中介者
class ConcreteMediator : public Mediator {
private:
    std::vector<Colleague*> colleagues;

public:
    void Register(Colleague* colleague) {
        colleagues.push_back(colleague);
    }

    void Send(const std::string& message, Colleague* colleague) override {
        for (auto* c : colleagues) {
            if (c != colleague) {
                c->Notify(message);
            }
        }
    }
};

// 抽象同事类
class Colleague {
protected:
    Mediator* mediator;

public:
    Colleague(Mediator* m) : mediator(m) {}
    virtual void Send(const std::string& message) = 0;
    virtual void Notify(const std::string& message) = 0;
};

// 具体同事类A
class ColleagueA : public Colleague {
public:
    ColleagueA(Mediator* m) : Colleague(m) {}

    void Send(const std::string& message) override {
        mediator->Send(message, this);
    }

    void Notify(const std::string& message) override {
        std::cout << "ColleagueA received: " << message << std::endl;
    }
};

// 具体同事类B
class ColleagueB : public Colleague {
public:
    ColleagueB(Mediator* m) : Colleague(m) {}

    void Send(const std::string& message) override {
        mediator->Send(message, this);
    }

    void Notify(const std::string& message) override {
        std::cout << "ColleagueB received: " << message << std::endl;
    }
};

int main() {
    std::unique_ptr<Mediator> mediator(new ConcreteMediator());
    ColleagueA a(mediator.get());
    ColleagueB b(mediator.get());

    mediator->Register(&a);
    mediator->Register(&b);

    a.Send("Hi ColleagueB!");
    b.Send("Hello ColleagueA!");

    return 0;
}
```

在这个示例中，`ConcreteMediator` 管理着所有同事对象，并负责在它们之间转发消息。`ColleagueA` 和 `ColleagueB` 是具体的同事类，它们通过中介者来发送和接收消息。这种方式使得同事类之间的耦合度降低，增加了代码的可维护性和可扩展性。

中介者模式的优点包括降低系统的耦合度、提高模块间的独立性以及提高了系统的可扩展性。然而，它也可能导致中介者对象变得复杂且难以维护，特别是当系统中的同事类数量很多时。因此，在设计时需要权衡中介者模式的利弊。

## 2.中介者模式优缺点

- 优点
  - 单一职责原则。 你可以将多个组件间的交流抽取到同一位置， 使其更易于理解和维护。
  - 开闭原则。 你无需修改实际组件就能增加新的中介者。
  - 你可以减轻应用中多个组件间的耦合情况。
  - 你可以更方便地复用各个组件。
- 缺点
  - 一段时间后， 中介者可能会演化成为上帝对象。

中介者模式（Mediator Pattern）的优缺点如下：

### 2.1.优点

1. **降低耦合度**：中介者模式可以减少类之间的直接通信，使得各个类之间的耦合度降低，只需要与中介者通信即可。

2. **提高模块化**：通过使用中介者模式，可以将对象间的交互逻辑从对象本身抽离出来，使得系统更加模块化，易于理解和维护。

3. **易于扩展**：新的组件可以很容易地加入到系统中，只需与中介者通信即可，无需修改其他组件的代码，符合开闭原则。

4. **集中控制**：中介者可以控制组件之间的交互逻辑，使得交互逻辑集中管理，便于控制和优化。

5. **减少子类数量**：中介者模式可以减少系统中的子类数量，因为交互逻辑被集中管理，不需要为每个组件创建子类来处理交互。

6. **可维护性**：当需要修改组件之间的交互逻辑时，只需修改中介者即可，不需要修改组件本身，提高了系统的可维护性。

### 2.2.缺点

1. **中介者复杂性**：随着系统的发展，中介者可能会变得越来越复杂，因为它需要处理所有组件之间的交互逻辑。

2. **性能问题**：如果中介者变得过于复杂，可能会成为系统的性能瓶颈，因为所有的交互都需要通过中介者来完成。

3. **单一中介者风险**：如果整个系统的组件都通过一个中介者来通信，那么这个中介者可能会成为系统的单点故障点。

4. **可测试性**：由于组件之间的交互被中介者封装，可能会使得组件的独立测试变得困难，需要为中介者编写额外的测试代码。

5. **过度使用**：在一些简单的系统中，或者组件之间的交互本身就不多的情况下，使用中介者模式可能会过度设计，增加不必要的复杂性。

6. **中介者职责过重**：如果中介者承担了过多的职责，可能会导致其变得庞大且难以维护，形成“上帝对象”（God Object）。

在使用中介者模式时，需要权衡这些优缺点，确保它适合解决系统面临的具体问题，并且不会引入新的问题。

## 3.中介者模式在实际项目中有哪些常见的应用场景？

中介者模式在实际项目中的应用场景非常广泛，以下是一些常见的例子：

1. **聊天室系统**：在聊天室系统中，用户之间的消息传递通过中介者模式来管理，这样可以避免用户之间的直接通信，简化了用户类之间的耦合，并使得通信策略的修改更加方便。

2. **图形用户界面（GUI）**：在GUI开发中，中介者模式常用于管理组件之间的交互，例如按钮、文本框和其他控件之间的通信。中介者可以是某个窗体或控制器，它负责协调各个组件的行为。

3. **网络游戏**：在网络游戏中，中介者模式可以用来管理玩家之间的交互，例如聊天、交易等。服务器作为中介者，处理玩家之间的请求和响应。

4. **企业信息系统**：在企业信息系统中，中介者模式可以用来协调不同业务模块之间的通信，例如订单处理、库存管理和客户服务等。

5. **硬件设备协调**：在智能家居或工业控制系统中，中介者模式可以用来协调各种设备之间的交互，例如灯光、温度控制、安全系统等。

6. **网络协议栈**：在网络通信中，中介者模式可以用来管理不同层次之间的数据传输和协议转换。

7. **框架和库**：在某些框架和库的设计中，中介者模式可以用来提供组件之间的通信机制，例如MVC模式中的控制器（C）就充当了中介者的角色。

8. **代码示例**：在C++中实现中介者模式通常涉及定义一个中介者接口和多个同事类，中介者负责协调同事类之间的交互。具体的中介者类实现了中介者接口，并包含了同事类之间的协调逻辑。

中介者模式的优点包括减少了组件之间的耦合，使得组件可以独立地变化和重用，同时也简化了组件之间的通信逻辑。然而，过度使用中介者模式可能会导致中介者本身变得复杂且难以维护，因此需要在设计时权衡其利弊。

## 4.如何判断一个系统是否适合使用中介者模式？

判断一个系统是否适合使用中介者模式，可以考虑以下几个关键点：

1. **组件之间的耦合度高**：如果系统中的多个组件相互依赖，形成了复杂的网状结构，这通常意味着它们之间存在过多的直接交互。使用中介者模式可以减少这种直接依赖，降低耦合度。

2. **需要集中控制**：当你需要对组件之间的交互进行集中控制和协调时，中介者模式非常有用。中介者可以控制消息的流向，以及何时、如何响应特定的事件。

3. **通信逻辑复杂**：如果组件之间的通信逻辑非常复杂，或者经常变化，将这些逻辑集中到中介者中可以简化组件的设计，使得组件不需要了解其他组件的内部实现。

4. **系统需要良好的可扩展性**：如果你希望系统能够容易地扩展新功能，中介者模式可以帮助你通过引入新的中介者或修改现有中介者来实现，而不需要对现有组件进行大量修改。

5. **存在多对多的交互**：在系统中，如果多个组件之间存在多对多的交互关系，这种复杂的交互关系难以管理和维护，使用中介者模式可以简化这些关系。

6. **需要重用组件**：如果你希望在不同的上下文中重用组件，而这些组件在不同的环境中需要与其他不同的组件交互，中介者模式可以提供一种灵活的方式来适应不同的交互需求。

7. **需要解耦组件**：如果你需要解耦组件之间的交互，以便单独开发和测试，中介者模式可以将交互逻辑从组件中分离出来，使得组件更加独立。

8. **存在跨组件的业务逻辑**：有时候，某些业务逻辑跨越了多个组件，这些逻辑不适合放在任何一个组件内部。这时，中介者可以作为一个合适的地点来实现这些跨组件的业务逻辑。

9. **需要统一的接口**：当需要为一组组件提供统一的交互接口时，中介者模式可以定义一个中介者接口，组件通过这个接口与中介者交互，而不是直接与其他组件交互。

10. **系统重构**：在系统重构过程中，如果发现组件之间的交互导致了代码的重复或难以维护，引入中介者模式可以帮助清理这些交互，提高系统的可维护性。

总的来说，如果你的系统存在上述情况之一或多个，那么使用中介者模式可能会带来好处。然而，也要注意不要过度使用中介者模式，因为一个过于复杂的中介者可能会成为系统中的瓶颈，导致新的维护问题。

## 5.中介者模式在设计时有哪些常见的问题和挑战？

在设计中介者模式时，可能会遇到以下常见问题和挑战：

1. **中介者职责过重**：随着系统的扩展，中介者可能会包含过多的逻辑，导致它变得复杂和难以管理。这可能违反单一职责原则，使得中介者本身成为系统中的瓶颈。

2. **难以维护和扩展**：中介者模式可能会导致中介者类变得庞大，难以维护。当需要添加新的行为或功能时，可能需要对中介者进行大量的修改，这增加了系统的脆弱性。

3. **性能问题**：中介者模式可能会引入额外的间接层，这可能会影响系统的性能。在高性能要求的场景中，这可能是一个考虑因素。

4. **过度使用**：在一些简单的系统中，或者组件之间的交互本身就不多的情况下，使用中介者模式可能会过度设计，增加不必要的复杂性。

5. **中介者与同事类的耦合**：虽然中介者模式旨在减少耦合，但中介者与同事类之间仍然存在一定的耦合。中介者需要知道所有同事类的引用，这可能会限制中介者的通用性。

6. **同事类之间的通信**：在某些情况下，同事类之间可能需要直接通信，而不是通过中介者。这种直接通信可能会绕过中介者，从而破坏了中介者模式的设计原则。

7. **中介者模式与其他模式的冲突**：在某些情况下，中介者模式可能与其他设计模式（如观察者模式）存在冲突。需要仔细考虑如何在系统中整合不同的模式。

8. **中介者模式的适用性**：在一些场景下，使用其他模式（如命令模式、策略模式）可能比中介者模式更合适。需要根据具体的业务需求和系统结构来选择合适的设计模式。

为了解决这些问题和挑战，可以采取以下措施：

- 确保中介者保持简洁，只包含必要的逻辑。
- 将中介者的责任划分为更小的单元，可能通过引入多个中介者来实现。
- 优化中介者的设计，确保它不会成为性能瓶颈。
- 仔细评估是否需要使用中介者模式，避免在不适当的情况下使用。
- 设计中介者和同事类的接口，确保它们之间的耦合最小化。
- 明确同事类之间的通信规则，确保所有通信都通过中介者进行。
- 在设计初期就考虑可能的扩展和维护需求，使系统更易于未来的修改。

通过这些方法，可以在设计中介者模式时避免常见的问题和挑战，从而创建一个更加健壮和可维护的系统。

## 6.中介者模式示例 cpp

下面是一个使用C++实现的中介者模式示例。这个例子模拟了一个简单的聊天系统，其中`ChatMediator`是中介者，`User`是同事类。

```cpp
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

// 抽象中介者
class ChatMediator {
public:
    virtual void sendMessage(const std::string& msg, User* user) = 0;
    virtual void addUser(User* user) = 0;
    virtual void removeUser(User* user) = 0;
};

// 具体中介者
class ChatRoom : public ChatMediator {
private:
    std::list<User*> users;

public:
    void sendMessage(const std::string& msg, User* user) override {
        for (auto* u : users) {
            if (u != user) {
                u->receive(msg);
            }
        }
    }

    void addUser(User* user) override {
        users.push_back(user);
    }

    void removeUser(User* user) override {
        users.remove(user);
    }
};

// 抽象同事类
class User {
protected:
    std::string name;
    ChatMediator* mediator;
public:
    User(const std::string& name, ChatMediator* mediator) : name(name), mediator(mediator) {}
    virtual void send(const std::string& msg) = 0;
    virtual void receive(const std::string& msg) = 0;
};

// 具体同事类
class UserImpl : public User {
public:
    UserImpl(const std::string& name, ChatMediator* mediator) : User(name, mediator) {}

    void send(const std::string& msg) override {
        mediator->sendMessage(msg, this);
    }

    void receive(const std::string& msg) override {
        std::cout << name << " received: " << msg << std::endl;
    }
};

int main() {
    ChatRoom chatRoom;
    UserImpl* user1 = new UserImpl("Alice", &chatRoom);
    UserImpl* user2 = new UserImpl("Bob", &chatRoom);

    chatRoom.addUser(user1);
    chatRoom.addUser(user2);

    user1->send("Hi Bob, how are you?");
    user2->send("Hi Alice, I'm good!");

    chatRoom.removeUser(user1);

    delete user1;
    delete user2;

    return 0;
}
```

在这个例子中，`ChatMediator`是一个抽象类，定义了发送消息的方法。`ChatRoom`是`ChatMediator`的具体实现，它管理一个用户列表，并负责将消息从一个用户转发给其他用户。

`User`是一个抽象类，定义了发送和接收消息的接口。`UserImpl`是`User`的具体实现，它通过中介者发送消息，并接收来自其他用户的消息。

在`main`函数中，我们创建了一个`ChatRoom`实例和两个`UserImpl`实例，并将用户添加到聊天室中。然后，每个用户通过中介者发送消息。最后，我们移除了一个用户。

这个例子展示了中介者模式如何帮助减少类之间的耦合，使得系统的各部分更加模块化和易于维护。

## 7.在C++中，有哪些工具或库可以帮助我更好地实现和测试设计模式？

在C++中，实现和测试设计模式时，有几个工具和库可以帮助你更高效地进行开发和测试：

1. **Visual Studio**：如果你使用的是Visual Studio，它提供了对C++单元测试的支持，包括Microsoft 单元测试框架、Google Test、Boost.Test和CTest。这些框架都可以帮助你在实现设计模式时编写和运行单元测试。Visual Studio还支持测试适配器，可以将单元测试与“测试资源管理器”窗口集成，方便管理和查看测试结果 。

2. **Google Test**：Google Test是一个由Google开发的C++单元测试框架，它提供了丰富的断言和测试组织机制，可以帮助你编写可读性好、易于维护的测试代码。

3. **Boost.Test**：Boost.Test是Boost库的一部分，它是一个跨平台的测试框架，提供了丰富的测试工具和测试组织方式。

4. **CMock**：CMock是一个轻量级的C/C++单元测试框架，它特别适合用于模拟对象和依赖注入，有助于在测试设计模式时进行解耦。

5. **Loki**：Loki是一个C++库，它提供了对一些设计模式的实现，如单例模式、工厂模式等。使用Loki库可以帮助你更容易地实现这些设计模式，并且它使用了大量的模板技巧，可以提高你的代码复用性 。

6. **gmock**：gmock是一个由Google开发的C++模拟框架，它可以与Google Test一起使用，为测试提供模拟对象和依赖注入功能，有助于在测试设计模式时进行解耦和模拟复杂的行为 。

7. **C++标准库**：C++标准库提供了许多有用的组件，如智能指针、容器和算法，它们可以帮助你实现设计模式时减少代码的复杂性。

8. **版本控制系统**：如Git，可以帮助你管理代码变更，特别是在多人协作和代码重构时。

9. **集成开发环境（IDE）**：如CLion、Eclipse CDT等，它们提供了代码提示、静态分析和调试工具，有助于提高代码质量和开发效率。

使用这些工具和库，你可以更容易地实现和测试设计模式，确保代码的质量和可维护性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
