#include <gtest/gtest.h>
#include <vector>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(StlContainersTest, RemovesEvenNumbersSafely) {
    std::vector<int> nums = {2, 1, 4, 6, 3, 5, 8};
    removeEvenNumbers(nums);
    std::vector<int> expected = {1, 3, 5};
    EXPECT_EQ(nums, expected);
}

TEST(StlContainersTest, CountsWordFrequencies) {
    std::vector<std::string> words = {"cpp", "stl", "cpp", "test", "stl", "cpp"};
    auto freq = countWordFrequencies(words);
    EXPECT_EQ(freq["cpp"], 3);
    EXPECT_EQ(freq["stl"], 2);
    EXPECT_EQ(freq["test"], 1);
}
