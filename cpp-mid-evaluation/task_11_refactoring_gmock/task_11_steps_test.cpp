#include "task_11_steps.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Common;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

namespace
{
    const Order regular_order{"a@b.com", "regular", "book", 2, 1000, "card"};

    template <typename Processor>
    void check_characterization(Processor& processor)
    {
        EXPECT_EQ(processor.process(regular_order), OrderStatus::Confirmed);
        EXPECT_EQ(processor.process({"a@b.com", "vip", "laptop", 3, 1000, "paypal"}), OrderStatus::OutOfStock);
        EXPECT_EQ(processor.process({"a@b.com", "regular", "pen", 1, 200000, "card"}), OrderStatus::PaymentFailed);
        EXPECT_EQ(processor.process({"a@b.com", "unknown", "pen", 1, 10, "card"}), OrderStatus::InvalidOrder);
        EXPECT_EQ(processor.process({"", "regular", "pen", 1, 10, "card"}), OrderStatus::InvalidOrder);
    }
} // namespace

// Steps 1-2: no seams yet, so only characterization tests (output is captured, not asserted in detail).
TEST(RefactoringSteps, Step1_PreservesBehavior)
{
    Step_1::OrderProcessor processor;
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    check_characterization(processor);
    EXPECT_THAT(testing::internal::GetCapturedStdout(), testing::HasSubstr("Charging card: 2000 cents"));
    testing::internal::GetCapturedStderr();
}

TEST(RefactoringSteps, Step2_PreservesBehavior)
{
    Step_2::OrderProcessor processor;
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    check_characterization(processor);
    EXPECT_THAT(testing::internal::GetCapturedStdout(), testing::HasSubstr("Sending e-mail to a@b.com"));
    testing::internal::GetCapturedStderr();
}

namespace
{
    class MockInventory : public Step_3::InventoryService
    {
    public:
        MOCK_METHOD(bool, reserve, (const std::string&, int), (override));
        MOCK_METHOD(void, release, (const std::string&, int), (override));
    };

    class MockPayments : public Step_3::PaymentGateway
    {
    public:
        MOCK_METHOD(bool, charge, (const std::string&, long long), (override));
    };

    class MockNotifier : public Step_3::NotificationService
    {
    public:
        MOCK_METHOD(void, order_confirmed, (const Order&), (override));
    };

    class NullLogger : public Step_3::Logger
    {
    public:
        void log(const std::string&) override { }
    };

    class MockPricing : public Step_4::PricingPolicy
    {
    public:
        MOCK_METHOD(std::optional<long long>, total_for, (const Order&), (const, override));
    };

    struct Fixture : ::testing::Test
    {
        MockInventory inventory;
        MockPayments payments;
        MockNotifier notifier;
        NullLogger logger;
    };
} // namespace

// Step 3: collaborators are mocked; the Step_3 processor still contains the pricing rules.
TEST_F(Fixture, Step3_ReservesChargesAndNotifiesInOrder)
{
    Step_3::OrderProcessor processor(inventory, payments, notifier, logger);
    InSequence seq;
    EXPECT_CALL(inventory, reserve("book", 2)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge("card", 2000)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(_));
    EXPECT_EQ(processor.process(regular_order), OrderStatus::Confirmed);
}

TEST_F(Fixture, Step3_FailedPaymentReleasesStockAndDoesNotNotify)
{
    Step_3::OrderProcessor processor(inventory, payments, notifier, logger);
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge(_, _)).WillOnce(Return(false));
    EXPECT_CALL(inventory, release("book", 2));
    EXPECT_CALL(notifier, order_confirmed(_)).Times(0);
    EXPECT_EQ(processor.process(regular_order), OrderStatus::PaymentFailed);
}

TEST_F(Fixture, Step3_VipPriceIsHardCodedInProcessor)
{
    Step_3::OrderProcessor processor(inventory, payments, notifier, logger);
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge("card", 1600)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(_));
    Order vip = regular_order;
    vip.customer_type = "vip";
    EXPECT_EQ(processor.process(vip), OrderStatus::Confirmed);
}

// Step 4: pricing is mocked too, so the processor is tested without any pricing rule.
TEST_F(Fixture, Step4_UsesPricingPolicyForChargedAmount)
{
    MockPricing pricing;
    Step_4::OrderProcessor processor(inventory, payments, notifier, logger, pricing);
    EXPECT_CALL(pricing, total_for(_)).WillOnce(Return(std::optional<long long>{777}));
    EXPECT_CALL(inventory, reserve(_, _)).WillOnce(Return(true));
    EXPECT_CALL(payments, charge("card", 777)).WillOnce(Return(true));
    EXPECT_CALL(notifier, order_confirmed(_));
    EXPECT_EQ(processor.process(regular_order), OrderStatus::Confirmed);
}

TEST_F(Fixture, Step4_UnsupportedCustomerTypeTouchesNoCollaborators)
{
    MockPricing pricing;
    Step_4::OrderProcessor processor(inventory, payments, notifier, logger, pricing);
    EXPECT_CALL(pricing, total_for(_)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(inventory, reserve(_, _)).Times(0);
    EXPECT_CALL(payments, charge(_, _)).Times(0);
    EXPECT_EQ(processor.process(regular_order), OrderStatus::InvalidOrder);
}

TEST(RefactoringSteps, Step4_NewCustomerTypeIsRegisteredWithoutEditingProcessor)
{
    Step_4::TieredPricing pricing;
    pricing.add_discount("regular", 0).add_discount("gold", 15);
    EXPECT_EQ(pricing.total_for({"a@b.com", "gold", "book", 2, 1000, "card"}), 1700);
    EXPECT_EQ(pricing.total_for({"a@b.com", "none", "book", 2, 1000, "card"}), std::nullopt);
}

