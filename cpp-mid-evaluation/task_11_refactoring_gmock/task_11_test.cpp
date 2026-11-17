#include <gmock/gmock.h>
#include <gtest/gtest.h>

#ifdef USE_SOLUTION
#include "task_11_solution.hpp"
using namespace Solution;
#else
#include "task_11.hpp"
#endif

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

class MockInventory : public InventoryService
{
public:
    MOCK_METHOD(bool, reserve, (const std::string& item, int quantity), (override));
};

class MockNotifier : public NotificationService
{
public:
    MOCK_METHOD(void, order_confirmed, (const Order& order), (override));
};

class StubInventory : public InventoryService
{
public:
    explicit StubInventory(bool can_reserve)
        : can_reserve_(can_reserve)
    {
    }
    bool reserve(const std::string&, int) override { return can_reserve_; }

private:
    bool can_reserve_;
};

TEST(RefactoringGmockTest, ConfirmsOrderAfterSuccessfulReservation)
{
    MockInventory inventory;
    MockNotifier notifier;
    OrderProcessor processor(inventory, notifier);
    const Order order{"book", 2};

    EXPECT_CALL(inventory, reserve(Eq("book"), 2)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(Eq(order)));
    EXPECT_TRUE(processor.process(order));
}

TEST(RefactoringGmockTest, DoesNotNotifyWhenReservationFails)
{
    StubInventory inventory(false);
    MockNotifier notifier;
    OrderProcessor processor(inventory, notifier);
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    EXPECT_FALSE(processor.process({"book", 2}));
}

TEST(RefactoringGmockTest, RejectsNonPositiveQuantity)
{
    MockInventory inventory;
    MockNotifier notifier;
    OrderProcessor processor(inventory, notifier);
    EXPECT_CALL(inventory, reserve(_, _)).Times(0);
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    EXPECT_FALSE(processor.process({"book", 0}));
}
