#include <gtest/gtest.h>
#include <utility>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(ValueMoveSemanticsTest, CreateProfileMovesArguments) {
    std::string name = "jan_kowalski";
    std::vector<int> pts = {10, 20, 30};

    auto profile = createProfile(std::move(name), std::move(pts));
    EXPECT_EQ(profile.username, "jan_kowalski");
    EXPECT_EQ(profile.scores.size(), 3u);
    EXPECT_TRUE(name.empty());
    EXPECT_TRUE(pts.empty());
}

TEST(ValueMoveSemanticsTest, ValueCategoriesAreCorrect) {
    int a = 10;
    EXPECT_EQ(classifyValueCategory(a), 1);
    EXPECT_EQ(classifyValueCategory(20), 2);
    EXPECT_EQ(classifyValueCategory(std::move(a)), 2);
    EXPECT_EQ(forwardTest(), 1);
}
