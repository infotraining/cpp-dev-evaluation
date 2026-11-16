#include <gtest/gtest.h>
#include <utility>

#ifdef USE_SOLUTION
#include "task_04_solution.hpp"
#else
#include "task_04_starter.hpp"
#endif

TEST(ValueMoveSemanticsTest, CreateProfileMovesArguments) {
    std::string name = "jan_kowalski";
    std::vector<int> pts = {10, 20, 30};

    auto profile = create_profile(std::move(name), std::move(pts));
    EXPECT_EQ(profile.username, "jan_kowalski");
    EXPECT_EQ(profile.scores.size(), 3u);
    EXPECT_TRUE(name.empty());
    EXPECT_TRUE(pts.empty());
}

TEST(ValueMoveSemanticsTest, ValueCategoriesAreCorrect) {
    int a = 10;
    EXPECT_EQ(classify_value_category(a), 1);
    EXPECT_EQ(classify_value_category(20), 2);
    EXPECT_EQ(classify_value_category(std::move(a)), 2);
    EXPECT_EQ(forward_test(), 1);
}
