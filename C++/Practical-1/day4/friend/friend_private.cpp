#include <iostream>

class Account {
private:
    double balance;

public:
    Account(double initialBalance) :
        balance(initialBalance) {
    }

    // 声明friend函数
    friend void displayBalance(const Account &account);
};

// friend函数定义
void displayBalance(const Account &account) {
    std::cout << "The balance is: $" << account.balance << std::endl;
}

int main() {
    Account myAccount(1000.0);
    displayBalance(myAccount);
    return 0;
}