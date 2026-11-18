#include <atomic>
#include <gtest/gtest.h>
#include <latch>
#include <stdexcept>
#include <thread>

#ifdef USE_SOLUTION
#include "task_07_solution.hpp"
using namespace Solution;
#else
#include "task_07.hpp"
#endif

TEST(WorkerCoordinationTest, StartsAllWorkersAndStopsCooperatively)
{
#ifndef USE_SOLUTION
    GTEST_SKIP() << "Starter code has no worker implementation yet.";
#else
    constexpr std::size_t worker_count = 3;
    std::latch entered(static_cast<std::ptrdiff_t>(worker_count));

    WorkerGroup group(worker_count, [&entered](std::stop_token token) {
        entered.count_down();
        while (!token.stop_requested())
        {
            std::this_thread::yield();
        }
    });

    group.start();

    entered.wait();

    group.request_stop();

    group.join();
#endif
}

TEST(WorkerCoordinationTest, RejectsInvalidConfiguration)
{
#ifdef USE_SOLUTION
    EXPECT_THROW((WorkerGroup(0, [](std::stop_token) { })), std::invalid_argument);
    EXPECT_THROW((WorkerGroup(1, {})), std::invalid_argument);
#else
    GTEST_SKIP() << "Starter code has no validation yet.";
#endif
}
