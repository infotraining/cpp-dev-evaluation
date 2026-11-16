#include <gtest/gtest.h>
#include "solution.hpp"

class BankAccountTest : public ::testing::Test {
protected:
    BankAccount account{100.0};
};

TEST_F(BankAccountTest, DepositIncreasesBalance) {
    account.deposit(50.0);
    EXPECT_DOUBLE_EQ(account.balance(), 150.0);
}

TEST_F(BankAccountTest, DepositNonPositiveThrows) {
    EXPECT_THROW(account.deposit(0.0), std::invalid_argument);
    EXPECT_THROW(account.deposit(-25.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(account.balance(), 100.0);
}

TEST_F(BankAccountTest, WithdrawDecreasesBalance) {
    account.withdraw(40.0);
    EXPECT_DOUBLE_EQ(account.balance(), 60.0);
}

TEST_F(BankAccountTest, WithdrawMoreThanBalanceThrows) {
    EXPECT_THROW(account.withdraw(100.01), std::runtime_error);
    EXPECT_DOUBLE_EQ(account.balance(), 100.0);
}
