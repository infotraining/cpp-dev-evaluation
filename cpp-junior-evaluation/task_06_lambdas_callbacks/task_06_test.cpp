#include <gtest/gtest.h>
#include <vector>

#ifdef USE_SOLUTION
#include "task_06_solution.hpp"
using namespace Solution;
#else
#include "task_06.hpp"
#endif

TEST(LambdasCallbacksTest, FiltersElementsAboveThreshold)
{
    std::vector<int> input = {1, 5, 10, 15, 20};
    auto res = filter_above_threshold(input, 10);
    ASSERT_EQ(res.size(), 2u);
    EXPECT_EQ(res[0], 15);
    EXPECT_EQ(res[1], 20);
}

TEST(LambdasCallbacksTest, DispatcherNotifiesAllSubscribers)
{
    EventDispatcher dispatcher;
    int sum = 0;
    int count = 0;

    dispatcher.subscribe([&sum](int code) { sum += code; });
    dispatcher.subscribe([&count](int) { ++count; });

    dispatcher.emit(5);
    dispatcher.emit(10);

    EXPECT_EQ(sum, 15);
    EXPECT_EQ(count, 2);
}
