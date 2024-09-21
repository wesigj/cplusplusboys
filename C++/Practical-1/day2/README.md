# C++ Practical-1 day2

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.求π

计算圆周率 \(\pi\) 的值可以通过多种算法实现。这里提供一个简单的 C++ 程序，使用莱布尼茨公式（Leibniz formula）来近似计算 \(\pi\) 的值。莱布尼茨公式是一个无穷级数，可以用来计算 \(\pi\)，公式如下：

\[
\pi = 4 \times \left(1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \cdots \right)
\]

下面是一个使用莱布尼茨公式计算 \(\pi\) 的 C++ 程序示例：

```cpp
#include <iostream>
#include <iomanip>

double calculatePi(int terms) {
    double sum = 0.0;
    for (int i = 0; i < terms; i++) {
        // 交替加减1/(2n-1)
        if (i % 2 == 0)
            sum += 1.0 / (2 * i + 1);
        else
            sum -= 1.0 / (2 * i + 1);
    }
    return 4 * sum;
}

int main() {
    int terms;
    std::cout << "Enter the number of terms to approximate Pi: ";
    std::cin >> terms;

    double pi = calculatePi(terms);
    std::cout << "Calculated Pi: " << std::setprecision(15) << pi << std::endl;

    return 0;
}
```

### 1.1.程序说明

1. **函数 `calculatePi`**：这个函数接受一个整数 `terms` 作为参数，表示级数的项数。函数通过循环计算莱布尼茨级数的和，然后乘以 4 得到 \(\pi\) 的近似值。
2. **主函数**：程序首先提示用户输入想要使用的项数。然后调用 `calculatePi` 函数，并输出计算得到的 \(\pi\) 值。

### 1.2.注意

- 项数越多，计算结果越精确，但计算时间也会增加。
- 莱布尼茨公式收敛速度非常慢，对于实际应用，通常使用更高效的算法，如高斯-勒让德算法、BBP公式等。

这个程序是一个简单的示例，用于展示如何在 C++ 中实现 \(\pi\) 的计算。对于高精度或性能要求，可能需要更复杂的算法。

## 2.enum

在C++中，`enum`（枚举）是一种用户定义的类型，它允许为一组相关的值定义一个名字。使用枚举可以提高代码的可读性和可维护性。

以下是一些C++中使用枚举的示例：

### 2.1.示例1：基础枚举

```cpp
#include <iostream>

enum Day {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

int main() {
    Day today = Wednesday;
    std::cout << "Today is: " << today << std::endl;
    std::cout << "Is today Friday? " << (today == Friday ? "Yes" : "No") << std::endl;
    return 0;
}
```

在这个示例中，`Day`是一个枚举类型，它定义了一周的七天。在`main`函数中，我们创建了一个`Day`类型的变量`today`，并将其设置为`Wednesday`。

### 2.2.示例2：带初始值的枚举

```cpp
#include <iostream>

enum Color : unsigned int {
    Red = 10,
    Green,
    Blue
};

int main() {
    std::cout << "Red is: " << Red << std::endl;   // 输出: Red is: 10
    std::cout << "Green is: " << Green << std::endl; // 输出: Green is: 11
    std::cout << "Blue is: " << Blue << std::endl;  // 输出: Blue is: 12
    return 0;
}
```

在这个示例中，`Color`是一个枚举类型，它从`Red`开始赋予初始值10，然后自动为`Green`和`Blue`分别赋予11和12。

### 2.3.示例3：基于字符串的枚举（C++11及以后）

```cpp
#include <iostream>

enum class Season {
    Spring,
    Summer,
    Autumn,
    Winter
};

int main() {
    Season favSeason = Season::Autumn;
    switch (favSeason) {
        case Season::Spring:
            std::cout << "Spring is the season of renewal." << std::endl;
            break;
        case Season::Summer:
            std::cout << "Summer is the season of heat." << std::endl;
            break;
        case Season::Autumn:
            std::cout << "Autumn is the season of harvest." << std::endl;
            break;
        case Season::Winter:
            std::cout << "Winter is the season of cold." << std::endl;
            break;
    }
    return 0;
}
```

在这个示例中，`Season`是一个枚举类型，我们使用`enum class`关键字来定义它。这种类型的枚举是强类型的，意味着我们必须使用`Season::`来指定枚举值。

### 2.4.示例4：指定底层类型的枚举（C++11及以后）

```cpp
#include <iostream>

enum class ErrorCode : int {
    None = 0,
    FileNotFound = 1,
    PermissionDenied = 2
};

int main() {
    ErrorCode error = ErrorCode::FileNotFound;
    std::cout << "Error code: " << static_cast<int>(error) << std::endl;
    return 0;
}
```

在这个示例中，`ErrorCode`是一个枚举类型，它的底层类型被指定为`int`。我们可以使用`static_cast<int>()`将枚举值转换为其底层的整数值。

枚举是C++中一种非常有用的构造，可以帮助我们以类型安全的方式处理一组相关的值。

## 3.汉诺塔

汉诺塔问题是一个经典的递归问题，涉及到将一组盘子从一个柱子移动到另一个柱子，同时通过一个中间柱子作为辅助。在移动过程中，任何时候较大的盘子都不能放在较小的盘子上面。目标是找到一种方法，使得所有盘子都从起始柱子移动到目标柱子。

下面是一个使用C++实现的汉诺塔问题的解决方案：

```cpp
#include <iostream>

// 递归函数，用于移动盘子
void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        std::cout << "Move disk 1 from rod " << from_rod << " to rod " << to_rod << std::endl;
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);
    std::cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << std::endl;
    hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n; // 盘子的数目

    std::cout << "Enter number of disks: ";
    std::cin >> n; // 用户输入盘子的数量

    // 调用递归函数开始解决汉诺塔问题
    hanoi(n, 'A', 'C', 'B'); // A为起始柱子，C为目标柱子，B为辅助柱子
    return 0;
}
```

### 3.1.程序说明

1. **函数 `hanoi`**：
   - 这是一个递归函数，接收四个参数：盘子数 `n`、起始柱子的字符标识符 `from_rod`、目标柱子的字符标识符 `to_rod` 和辅助柱子的字符标识符 `aux_rod`。
   - 如果只有一个盘子（`n == 1`），直接将其从起始柱子移动到目标柱子。
   - 如果有多于一个盘子，算法分为三步：
     1. 先移动上面的 `n-1` 个盘子，从起始柱子借助目标柱子移动到辅助柱子。
     2. 将最大的盘子，也就是最底下的盘子，直接从起始柱子移动到目标柱子。
     3. 最后再将那 `n-1` 个盘子从辅助柱子借助起始柱子移动到目标柱子。

2. **主函数 `main`**：
   - 用户输入盘子的数量。
   - 调用 `hanoi` 函数开始解决汉诺塔问题。

这个程序展示了如何使用递归方法解决汉诺塔问题。递归是解决这类问题的强大工具，因为它可以自然地分解问题为更小的子问题。

## 4.x^n x的n次方

计算 \(x\) 的 \(n\) 次方是一个常见的数学运算，可以通过多种方式在C++中实现。下面是一个简单的C++程序，用于计算 \(x\) 的 \(n\) 次方：

### 4.1.示例1：使用循环

```cpp
#include <iostream>
#include <cmath>  // 用于abs函数

double power(double x, int n) {
    double result = 1;
    bool negative = n < 0;
    n = abs(n);

    for (int i = 0; i < n; i++) {
        result *= x;
    }

    return negative ? 1 / result : result;
}

int main() {
    double x;
    int n;
    std::cout << "Enter base (x): ";
    std::cin >> x;
    std::cout << "Enter exponent (n): ";
    std::cin >> n;

    double result = power(x, n);
    std::cout << x << " raised to the power " << n << " is " << result << std::endl;

    return 0;
}
```

### 4.2.示例2：使用递归

```cpp
#include <iostream>
#include <cmath>  // 用于abs函数

double power(double x, int n) {
    if (n == 0) {
        return 1;  // 任何数的0次方都是1
    }
    if (n < 0) {
        return 1 / power(x, -n);  // 负指数转换为正指数的倒数
    }
    double half = power(x, n / 2);
    if (n % 2 == 0) {
        return half * half;
    } else {
        return half * half * x;
    }
}

int main() {
    double x;
    int n;
    std::cout << "Enter base (x): ";
    std::cin >> x;
    std::cout << "Enter exponent (n): ";
    std::cin >> n;

    double result = power(x, n);
    std::cout << x << " raised to the power " << n << " is " << result << std::endl;

    return 0;
}
```

### 4.3.程序说明

1. **函数 `power`**：
   - 接受两个参数：基数 `x` 和指数 `n`。
   - 使用循环或递归方法计算 \(x^n\)。
   - 如果指数为负，计算 \(x\) 的 \(-n\) 次方，然后取倒数。

2. **主函数 `main`**：
   - 用户输入基数 \(x\) 和指数 \(n\)。
   - 调用 `power` 函数计算结果，并输出。

这两个示例展示了如何使用循环和递归方法来计算幂。递归方法更简洁，但循环方法在处理非常大的指数时可能更高效。在实际应用中，你可以根据需要选择适合的方法。

## 5.递归

递归是一种在函数中调用自身来解决问题的方法。递归通常用于那些可以分解为更小、更简单问题的情况。在C++中，递归经常被用来解决诸如汉诺塔、斐波那契数列、阶乘计算等问题。

下面是一个简单的C++递归示例，计算阶乘：

### 5.1.示例：阶乘的递归计算

```cpp
#include <iostream>

// 递归函数，用于计算阶乘
unsigned long long factorial(int n) {
    if (n == 0) { // 递归终止条件
        return 1;
    }
    return n * factorial(n - 1); // 递归调用
}

int main() {
    int number;
    std::cout << "Enter a positive integer: ";
    std::cin >> number;

    // 检查输入是否为正整数
    if (number < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    } else {
        unsigned long long result = factorial(number);
        std::cout << "Factorial of " << number << " = " << result << std::endl;
    }

    return 0;
}
```

### 5.2.程序说明

1. **函数 `factorial`**：
   - 这是一个递归函数，用于计算一个整数的阶乘。
   - 如果 `n` 为 0（递归终止条件），函数返回 1，因为0的阶乘定义为1。
   - 如果 `n` 大于 0，函数通过 `n * factorial(n - 1)` 进行递归调用。

2. **主函数 `main`**：
   - 用户输入一个正整数。
   - 程序检查输入是否为正整数。
   - 如果是，调用 `factorial` 函数计算阶乘，并输出结果。

递归函数必须有一个终止条件，否则它将无限递归下去，最终导致栈溢出错误。在上述示例中，当 `n` 等于 0 时递归终止。

递归虽然是一个强大的工具，但它也有缺点，如可能导致堆栈溢出（如果递归太深），以及可能比迭代解决方案更慢。因此，使用递归时需要谨慎，并确保有一个明确的终止条件。

## 6.掷骰子

在C++中，模拟掷骰子的过程通常涉及到生成随机数。以下是一个简单的C++程序，用于模拟掷一个六面骰子的过程：

```cpp
#include <iostream>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()

int main() {
    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(0)));

    // 生成一个1到6的随机数
    int dice = rand() % 6 + 1;

    std::cout << "You rolled a dice and got: " << dice << std::endl;

    return 0;
}
```

### 6.1.程序说明

1. **包含头文件**：
   - `<iostream>` 用于输入输出。
   - `<cstdlib>` 包含`rand()`和`srand()`函数。
   - `<ctime>` 包含`time()`函数。

2. **初始化随机数生成器**：
   - `srand()`函数用于设置随机数生成器的种子值，通常使用当前时间作为种子，通过`time(0)`获得。

3. **生成随机数**：
   - `rand() % 6 + 1`生成一个1到6的随机数，模拟掷一个六面骰子的结果。

4. **输出结果**：
   - 使用`std::cout`输出掷骰子的结果。

### 6.2.更复杂的示例：多次掷骰子

下面的程序模拟掷两个骰子多次，并计算点数之和的频率：

```cpp
#include <iostream>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <map>

int main() {
    const int rolls = 100000; // 掷骰子的次数
    const int diceCount = 2;  // 骰子的数量
    std::map<int, int> frequency; // 用于存储点数之和的频率

    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < rolls; ++i) {
        int sum = 0;
        for (int j = 0; j < diceCount; ++j) {
            sum += rand() % 6 + 1; // 每个骰子的点数
        }
        ++frequency[sum]; // 更新频率
    }

    std::cout << "Sum Frequency after " << rolls << " rolls:" << std::endl;
    for (const auto &kv : frequency) {
        std::cout << "Sum " << kv.first << " appears " << kv.second << " times." << std::endl;
    }

    return 0;
}
```

### 6.3.程序说明

1. **定义常量**：
   - `rolls` 表示掷骰子的次数。
   - `diceCount` 表示骰子的数量。

2. **初始化随机数生成器**：
   - 使用当前时间作为种子。

3. **循环掷骰子**：
   - 每次循环掷两个骰子，计算点数之和。

4. **更新频率**：
   - 使用`std::map`记录每个点数之和的出现次数。

5. **输出结果**：
   - 输出每个点数之和的出现次数。

这个程序可以扩展到更多的骰子和更复杂的规则，例如在桌面游戏中使用。

---

## 7.struct

在C++中，结构体（`struct`）是一种复合数据类型，允许你将多个不同的数据类型组合成一个单一的数据结构。结构体经常用于表示记录。

以下是定义和使用结构体的基本示例：

### 7.1.示例1：定义和使用简单的结构体

```cpp
#include <iostream>

// 定义一个结构体，用于表示点
struct Point {
    int x;
    int y;
};

int main() {
    // 创建一个点
    Point p;
    p.x = 10;
    p.y = 20;

    // 输出点的坐标
    std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;

    // 创建另一个点
    Point q = {5, 15}; // 列表初始化

    // 修改并输出点的坐标
    std::cout << "Point: (" << q.x << ", " << q.y << ")" << std::endl;

    return 0;
}
```

### 7.2.示例2：定义和使用包含函数的结构体

C++11允许在结构体中定义函数，这使得结构体可以包含方法。

```cpp
#include <iostream>
#include <cmath> // 用于sqrt函数

// 定义一个结构体，用于表示点，并包含一个方法
struct Point {
    int x, y;

    // 方法：计算点到原点的距离
    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }
};

int main() {
    Point p = {3, 4};

    std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;
    std::cout << "Distance to origin: " << p.distanceToOrigin() << std::endl;

    return 0;
}
```

### 7.3.示例3：定义和使用包含构造函数的结构体

C++11也允许在结构体中定义构造函数。

```cpp
#include <iostream>
#include <cmath> // 用于sqrt函数

// 定义一个结构体，用于表示点，并包含构造函数
struct Point {
    int x, y;

    // 构造函数
    Point(int x, int y) : x(x), y(y) {}

    // 方法：计算点到原点的距离
    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }
};

int main() {
    Point p(3, 4);

    std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;
    std::cout << "Distance to origin: " << p.distanceToOrigin() << std::endl;

    return 0;
}
```

### 7.4.示例4：定义和使用结构体数组

```cpp
#include <iostream>

// 定义一个结构体，用于表示矩形
struct Rectangle {
    int width;
    int height;
};

int main() {
    // 创建一个矩形数组
    Rectangle rectangles[2] = {
        {10, 20},
        {30, 40}
    };

    // 遍历数组并输出每个矩形的尺寸
    for (int i = 0; i < 2; ++i) {
        std::cout << "Rectangle " << i + 1 << ": "
                  << "width = " << rectangles[i].width
                  << ", height = " << rectangles[i].height << std::endl;
    }

    return 0;
}
```

结构体在C++中非常有用，它们可以包含数据和函数，使得数据的组织和操作更加方便。

## 8.在C++中，如何使用结构体来模拟一个简单的银行账户系统？

在C++中，你可以使用结构体来模拟一个简单的银行账户系统。以下是一个示例，展示了如何定义一个银行账户结构体，并提供了存款、取款和显示账户信息的功能：

```cpp
#include <iostream>

// 定义银行账户结构体
struct BankAccount {
    std::string owner; // 账户持有人姓名
    long accountNumber; // 账户号码
    double balance; // 账户余额
};

// 存款函数
void deposit(BankAccount &account, double amount) {
    if (amount > 0) {
        account.balance += amount;
        std::cout << "Deposited: " << amount << std::endl;
    } else {
        std::cout << "Invalid deposit amount" << std::endl;
    }
    std::cout << "Current balance: " << account.balance << std::endl;
}

// 取款函数
void withdraw(BankAccount &account, double amount) {
    if (amount > 0 && account.balance >= amount) {
        account.balance -= amount;
        std::cout << "Withdrew: " << amount << std::endl;
    } else {
        std::cout << "Invalid or insufficient funds" << std::endl;
    }
    std::cout << "Current balance: " << account.balance << std::endl;
}

// 显示账户信息函数
void displayAccountInfo(const BankAccount &account) {
    std::cout << "Account owner: " << account.owner << std::endl;
    std::cout << "Account number: " << account.accountNumber << std::endl;
    std::cout << "Account balance: " << account.balance << std::endl;
}

int main() {
    // 创建一个银行账户实例
    BankAccount myAccount = {"John Doe", 123456789L, 1000.0};

    // 显示账户信息
    displayAccountInfo(myAccount);

    // 进行存款操作
    deposit(myAccount, 200.0);

    // 进行取款操作
    withdraw(myAccount, 500.0);

    // 再次显示账户信息
    displayAccountInfo(myAccount);

    return 0;
}
```

### 8.1.程序说明

1. **定义结构体**：
   - `BankAccount` 结构体包含三个成员：`owner`（持有人姓名），`accountNumber`（账户号码），`balance`（账户余额）。

2. **定义函数**：
   - `deposit` 函数接受一个账户引用和存款金额，如果金额有效，则将其添加到账户余额中。
   - `withdraw` 函数接受一个账户引用和取款金额，如果取款金额有效且账户余额足够，则从账户余额中扣除。
   - `displayAccountInfo` 函数接受一个账户引用，并显示账户的详细信息。

3. **主函数**：
   - 创建一个 `BankAccount` 类型的实例 `myAccount`。
   - 调用 `displayAccountInfo` 函数显示账户信息。
   - 调用 `deposit` 函数进行存款操作。
   - 调用 `withdraw` 函数进行取款操作。
   - 最后再次调用 `displayAccountInfo` 函数显示账户信息。

这个程序展示了如何使用结构体和函数来模拟一个简单的银行账户系统。你可以根据需要扩展这个系统，例如添加密码验证、交易历史记录等功能。

## 9.static

在C++中，`static`关键字有多种用途，包括：

1. **局部静态变量**：在函数内部，`static`用于定义一个静态局部变量，这意味着变量的生命周期将持续到程序结束，而不仅仅是函数调用期间。

2. **全局静态变量**：在函数外部，`static`用于定义一个全局变量，它的生命周期将持续到程序结束，但它的链接是局部的，只能在定义它的文件中访问。

3. **静态成员变量**：在类中，`static`用于定义静态成员变量，这意味着该变量不是与类的具体实例相关联的，而是被类的所有实例共享。

4. **静态成员函数**：在类中，`static`用于定义静态成员函数，这意味着该函数可以在没有类实例的情况下调用。

5. **静态类成员**：在类模板中，`static`用于定义静态成员，这要求在类外初始化。

以下是一些使用`static`的示例：

### 9.1.示例1：局部静态变量

```cpp
#include <iostream>

void function() {
    static int local_static_var = 1;
    local_static_var++;
    std::cout << local_static_var << std::endl;
}

int main() {
    function();
    function();
    function();
    return 0;
}
```

在这个示例中，`local_static_var`是一个静态局部变量，它在函数第一次调用时被初始化，然后在随后的调用中保持其值。

### 9.2.示例2：全局静态变量

```cpp
#include <iostream>

static int global_static_var = 10;

int main() {
    std::cout << "global_static_var: " << global_static_var << std::endl;
    global_static_var++;
    std::cout << "global_static_var: " << global_static_var << std::endl;
    return 0;
}
```

在这个示例中，`global_static_var`是一个静态全局变量，它只能在定义它的文件中访问。

### 9.3.示例3：静态成员变量

```cpp
#include <iostream>

class MyClass {
public:
    static int staticMember;
};

int MyClass::staticMember = 0;

int main() {
    MyClass::staticMember = 100;
    std::cout << "MyClass::staticMember: " << MyClass::staticMember << std::endl;
    return 0;
}
```

在这个示例中，`staticMember`是一个静态成员变量，可以通过类名直接访问。

### 9.4.示例4：静态成员函数

```cpp
#include <iostream>

class MyClass {
public:
    static void staticMemberFunction() {
        std::cout << "This is a static member function." << std::endl;
    }
};

int main() {
    MyClass::staticMemberFunction();
    return 0;
}
```

在这个示例中，`staticMemberFunction`是一个静态成员函数，可以在没有类实例的情况下调用。

### 9.5.示例5：静态类模板成员

```cpp
#include <iostream>
#include <string>

template <typename T>
class MyClass {
public:
    static std::string staticMember;
};

template <typename T>
std::string MyClass<T>::staticMember = "Hello, World!";

int main() {
    std::cout << "MyClass<int>::staticMember: " << MyClass<int>::staticMember << std::endl;
    std::cout << "MyClass<double>::staticMember: " << MyClass<double>::staticMember << std::endl;
    return 0;
}
```

在这个示例中，`staticMember`是一个静态成员，它在类模板中定义，并在类外初始化。

`static`关键字是C++中一个非常有用的工具，可以用于多种场景，包括控制变量的生命周期和访问级别，以及实现类成员的特殊行为。

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
