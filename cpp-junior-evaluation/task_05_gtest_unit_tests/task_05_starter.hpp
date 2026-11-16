#pragma once
#include <stdexcept>

class BankAccount {
public:
    explicit BankAccount(double initialBalance) : balance_(initialBalance) {
        if (initialBalance < 0.0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
    }

    void deposit(double amount) {
        if (amount <= 0.0) {
            throw std::invalid_argument("Deposit must be positive");
        }
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0.0) {
            throw std::invalid_argument("Withdrawal must be positive");
        }
        if (amount > balance_) {
            throw std::runtime_error("Insufficient funds");
        }
        balance_ -= amount;
    }

    double balance() const { return balance_; }

private:
    double balance_;
};
