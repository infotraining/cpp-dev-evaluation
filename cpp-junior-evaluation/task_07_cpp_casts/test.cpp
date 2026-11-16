#include <gtest/gtest.h>
#include <vector>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(CppCastsTest, CountsDevelopersUsingDynamicCast) {
    Developer d1, d2;
    Manager m1;
    std::vector<Employee*> staff = {&d1, &m1, nullptr, &d2};

    EXPECT_EQ(countDevelopers(staff), 2);
}

TEST(CppCastsTest, TruncatesDoubleAndCallsLegacyApi) {
    EXPECT_EQ(truncateToInt(3.99), 3);
    EXPECT_NO_THROW(callLegacyApi("Hello Legacy"));
}
