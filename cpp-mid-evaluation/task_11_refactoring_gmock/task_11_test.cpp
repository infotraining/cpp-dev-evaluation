#include <gmock/gmock.h>
#include <gtest/gtest.h>

#ifdef USE_SOLUTION
#include "task_11_solution.hpp"
using namespace Solution;

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;

class MockInventory : public InventoryService
{
public:
    MOCK_METHOD(bool, reserve, (const std::string& item, int quantity), (override));
    MOCK_METHOD(void, release, (const std::string& item, int quantity), (override));
};

class MockPayments : public PaymentGateway
{
public:
    MOCK_METHOD(bool, charge, (const std::string& method, long long amount_cents), (override));
};

class MockNotifier : public NotificationService
{
public:
    MOCK_METHOD(void, order_confirmed, (const Order& order), (override));
};

// Stub: no expectations, we only need a silent collaborator.
class NullLogger : public Logger
{
public:
    void log(const std::string&) override { }
};

class NoDiscount : public DiscountPolicy
{
public:
    long long apply(long long total) const override { return total; }
};

class OrderProcessorTest : public ::testing::Test
{
protected:
    MockInventory inventory;
    MockPayments payments;
    MockNotifier notifier;
    NullLogger logger;
    NoDiscount no_discount;
    PercentageDiscount ten_percent{10};
    const Order order{"a@b.com", "regular", "book", 2, 1000, "card"};

    OrderStatus process_with(const DiscountPolicy& policy, const Order& o)
    {
        OrderProcessor processor(inventory, payments, notifier, logger, policy);
        return processor.process(o);
    }
};

TEST_F(OrderProcessorTest, ReservesChargesAndNotifiesInOrder)
{
    InSequence seq;
    EXPECT_CALL(inventory, reserve("book", 2)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge("card", 2000)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(_));
    EXPECT_EQ(process_with(no_discount, order), OrderStatus::Confirmed);
}

TEST_F(OrderProcessorTest, AppliesDiscountPolicyToChargedAmount)
{
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge("card", 1800)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(_));
    EXPECT_EQ(process_with(ten_percent, order), OrderStatus::Confirmed);
}

TEST_F(OrderProcessorTest, OutOfStockDoesNotChargeOrNotify)
{
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(false));
    EXPECT_CALL(payments, charge(_, _)).Times(0);
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    EXPECT_EQ(process_with(no_discount, order), OrderStatus::OutOfStock);
}

TEST_F(OrderProcessorTest, FailedPaymentReleasesStockAndDoesNotNotify)
{
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge(_, _)).WillOnce(Return(false));
    EXPECT_CALL(inventory, release("book", 2));
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    EXPECT_EQ(process_with(no_discount, order), OrderStatus::PaymentFailed);
}

TEST_F(OrderProcessorTest, InvalidOrderTouchesNoCollaborators)
{
    EXPECT_CALL(inventory, reserve(_, _)).Times(0);
    EXPECT_CALL(payments, charge(_, _)).Times(0);
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    Order bad = order;
    bad.quantity = 0;
    EXPECT_EQ(process_with(no_discount, bad), OrderStatus::InvalidOrder);
}
#else
#include "task_11.hpp"

// Characterization tests of the original god class. Replace them with isolated tests:
// extract interfaces, inject them, and use mocks/stubs (see README).
TEST(OrderProcessorCharacterization, ConfirmsValidOrder)
{
    OrderProcessor processor;
    EXPECT_EQ(processor.process({"a@b.com", "regular", "book", 2, 1000, "card"}), OrderStatus::Confirmed);
}

TEST(OrderProcessorCharacterization, ReportsOutOfStock)
{
    OrderProcessor processor;
    EXPECT_EQ(processor.process({"a@b.com", "regular", "laptop", 3, 1000, "paypal"}), OrderStatus::OutOfStock);
}
#endif
