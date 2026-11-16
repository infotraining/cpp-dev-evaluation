#include <gtest/gtest.h>
#include <vector>

#ifdef USE_SOLUTION
#include "task_08_solution.hpp"
#else
#include "task_08_starter.hpp"
#endif

TEST(StlContainersTest, RemovesEvenNumbersSafely) {
    std::vector<int> nums = {2, 1, 4, 6, 3, 5, 8};
    remove_even_numbers(nums);
    std::vector<int> expected = {1, 3, 5};
    EXPECT_EQ(nums, expected);
}

TEST(StlContainersTest, CountsWordFrequencies) {
    std::vector<std::string> words = {"cpp", "stl", "cpp", "test", "stl", "cpp"};
    auto freq = count_word_frequencies(words);
    EXPECT_EQ(freq["cpp"], 3);
    EXPECT_EQ(freq["stl"], 2);
    EXPECT_EQ(freq["test"], 1);
}
