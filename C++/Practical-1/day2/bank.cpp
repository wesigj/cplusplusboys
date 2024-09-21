#include <iostream>

// 定义银行账户结构体
struct BankAccount {
    std::string owner;         // 账户持有人姓名
    long        accountNumber; // 账户号码
    double      balance;       // 账户余额
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