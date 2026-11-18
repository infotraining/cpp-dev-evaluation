#include <gtest/gtest.h>
#include <memory>

#ifdef USE_SOLUTION
#include "task_02_solution.hpp"
using namespace Solution;
#else
#include "task_02.hpp"
#endif

TEST(SmartPointersTest_Solution, PacketBufferTransferOwnership)
{
    PacketBuffer buf(64);
    EXPECT_EQ(buf.size(), 64u);

    auto rawPtr = buf.release_buffer();
    EXPECT_NE(rawPtr, nullptr);
    EXPECT_EQ(buf.size(), 0u);
}

TEST(SmartPointersTest_Solution, WeakPtrBreaksCycle)
{
    std::weak_ptr<NodeA> observerA;
    std::shared_ptr<NodeB> b = std::make_shared<NodeB>();

    {
        auto a = std::make_shared<NodeA>();
        observerA = a;
        a->next = b;
        b->prev = a;
        EXPECT_TRUE(b->has_valid_prev());
    }

    EXPECT_TRUE(observerA.expired());
    EXPECT_FALSE(b->has_valid_prev());
}

struct TestObserver : public Observer
{
    inline static int instance_count;

    TestObserver(std::string name)
        : name(std::move(name))
    {
        ++instance_count;
    }

    TestObserver(const TestObserver&) = delete;
    TestObserver& operator=(const TestObserver&) = delete;

    ~TestObserver()
    {
        --instance_count;
    }

    std::string name;
    int last_value = 0;

    void update(int value) override
    {
        last_value = value;
    }
};

TEST(SmartPointersTest_Solution, ObserverPattern)
{
    TestObserver::instance_count = 0;

    auto sensor = std::make_shared<TemperatureSensor>();

    auto observer_1 = std::make_shared<TestObserver>("observer_1");
    sensor->attach(observer_1);

    EXPECT_EQ(TestObserver::instance_count, 1);

    {
        auto observer_2 = std::make_shared<TestObserver>("observer_2");
        sensor->attach(observer_2);

        EXPECT_EQ(TestObserver::instance_count, 2);

        sensor->set_temperature(20);
        EXPECT_EQ(observer_1->last_value, 20);
        EXPECT_EQ(observer_2->last_value, 20);
    }

    sensor->set_temperature(25);
    EXPECT_EQ(observer_1->last_value, 25);
    EXPECT_EQ(TestObserver::instance_count, 1);
}
