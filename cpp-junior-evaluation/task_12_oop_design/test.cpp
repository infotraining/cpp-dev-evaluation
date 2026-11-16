#include <gtest/gtest.h>
#include <string>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(OopDesignTest, DateEnforcesInvariants) {
    EXPECT_THROW(SimpleDate(32, 5, 2025), std::invalid_argument);
    EXPECT_THROW(SimpleDate(10, 13, 2025), std::invalid_argument);

    SimpleDate d(15, 6, 2025);
    EXPECT_THROW(d.setMonth(0), std::invalid_argument);
    EXPECT_EQ(d.month(), 6);
}

TEST(OopDesignTest, NotificationServiceUsesComposition) {
    struct MockLogger : public ILogger {
        std::string lastMessage;
        void log(const std::string& msg) override { lastMessage = msg; }
    };

    MockLogger logger;
    NotificationService service(logger);
    service.sendAlert("admin");

    EXPECT_EQ(logger.lastMessage, "Alert sent to: admin");
}
