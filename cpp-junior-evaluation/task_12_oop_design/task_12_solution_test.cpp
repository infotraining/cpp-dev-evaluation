#include <gtest/gtest.h>
#include <string>

#ifdef USE_SOLUTION
#include "task_12_solution.hpp"
using namespace Solution;
#else
#include "task_12.hpp"
#endif

TEST(OopDesignTest, DateEnforcesInvariants)
{
    EXPECT_THROW(SimpleDate(32, 5, 2025), std::invalid_argument);
    EXPECT_THROW(SimpleDate(10, 13, 2025), std::invalid_argument);

    SimpleDate d(15, 6, 2025);
    EXPECT_THROW(d.set_month(0), std::invalid_argument);
    EXPECT_EQ(d.month(), 6);
}

TEST(OopDesignTest, NotificationServiceUsesComposition)
{
    struct MockLogger : public ILogger
    {
        std::string lastMessage;
        void log(const std::string& msg) override { lastMessage = msg; }
    };

    MockLogger logger;
    NotificationService service(logger);
    service.send_alert("admin");

    EXPECT_EQ(logger.lastMessage, "Alert sent to: admin");
}
