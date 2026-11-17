#include <deque>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <list>
#include <ranges>
#include <vector>

#ifdef USE_SOLUTION
#include "task_08_solution.hpp"
using namespace Solution;
#else
#include "task_08.hpp"
#endif

TEST(StlContainersTest_Solution, RemovesEvenNumbersSafely)
{
    std::vector<int> nums = {2, 1, 4, 6, 3, 5, 8};
    remove_even_numbers(nums);
    std::vector<int> expected = {1, 3, 5};
    EXPECT_EQ(nums, expected);
}

TEST(StlContainersTest_Solution, CountsWordFrequencies)
{
    std::vector<std::string> words = {"cpp", "stl", "cpp", "test", "stl", "cpp"};
    auto freq = count_word_frequencies(words);
    EXPECT_EQ(freq["cpp"], 3);
    EXPECT_EQ(freq["stl"], 2);
    EXPECT_EQ(freq["test"], 1);
}

template <typename T>
concept StringLike = std::is_convertible_v<T, std::string>;

template <std::ranges::range T>
    requires(!StringLike<T>)
std::ostream& operator<<(std::ostream& os, const T& vec)
{
    os << "[ ";
    for (const auto& elem : vec)
        os << elem << " ";
    os << " ]";
    return os;
}

// ============================================================================
// TYPED_TEST_SUITE: Test move_chunk_of_container_to with multiple container types
// ============================================================================

// Define type pairs: (SourceContainer, DestinationContainer)
using ContainerTypePairs = ::testing::Types<
    std::pair<std::vector<int>, std::vector<int>>,
    std::pair<std::vector<int>, std::deque<int>>,
    std::pair<std::vector<int>, std::list<int>>,
    std::pair<std::deque<int>, std::vector<int>>,
    std::pair<std::deque<int>, std::deque<int>>,
    std::pair<std::deque<int>, std::list<int>>,
    std::pair<std::list<int>, std::vector<int>>,
    std::pair<std::list<int>, std::deque<int>>,
    std::pair<std::list<int>, std::list<int>>>;

template <typename TypePair>
class MoveChunkOfContainerToTest : public ::testing::Test
{
public:
    using SourceType = typename TypePair::first_type;
    using DestinationType = typename TypePair::second_type;

    // Helper: Convert source to string for readability
    std::string container_name()
    {
        std::string src, dst;
        if constexpr (std::same_as<SourceType, std::vector<int>>)
            src = "vector";
        else if constexpr (std::same_as<SourceType, std::deque<int>>)
            src = "deque";
        else if constexpr (std::same_as<SourceType, std::list<int>>)
            src = "list";

        if constexpr (std::same_as<DestinationType, std::vector<int>>)
            dst = "vector";
        else if constexpr (std::same_as<DestinationType, std::deque<int>>)
            dst = "deque";
        else if constexpr (std::same_as<DestinationType, std::list<int>>)
            dst = "list";

        return src + "->" + dst;
    }
};

TYPED_TEST_SUITE(MoveChunkOfContainerToTest, ContainerTypePairs);

TYPED_TEST(MoveChunkOfContainerToTest, MovesComplexRangeWithDuplicates)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    // Create source as sorted sequence
    SourceType source{1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9, 9, 10, 10, 11, 12, 13, 14, 15};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 5, 10);

    // Convert to vector for comparison
    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({5, 5, 5, 6, 7, 8, 9, 9, 10, 10})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({1, 2, 3, 4, 11, 12, 13, 14, 15})) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, MovesBeginningRange)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{1, 2, 3, 4, 5};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 1, 3);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({1, 2, 3})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({4, 5})) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, AppendsToPreffilledDestination)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{10, 20, 30, 40, 50};
    DestinationType destination{100, 200};

    move_chunk_of_container_to(source, destination, 20, 40);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({100, 200, 20, 30, 40})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({10, 50})) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, MovesAllIdenticalValues)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{5, 5, 5, 5};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 5, 5);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({5, 5, 5, 5})) << "Test: " << this->container_name();
    EXPECT_TRUE(source_vec.empty()) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, MovesSingleElementAtStart)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 1, 1);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({1})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({2, 3, 4, 5, 6, 7, 8, 9, 10})) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, MovesSingleElementAtEnd)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 10, 10);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({10})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9})) << "Test: " << this->container_name();
}

TYPED_TEST(MoveChunkOfContainerToTest, MovesMiddleRange)
{
    using SourceType = typename TypeParam::first_type;
    using DestinationType = typename TypeParam::second_type;

    SourceType source{1, 2, 3, 4, 5, 6, 7, 8};
    DestinationType destination{};

    move_chunk_of_container_to(source, destination, 3, 6);

    std::vector<int> dest_vec(destination.begin(), destination.end());
    std::vector<int> source_vec(source.begin(), source.end());

    EXPECT_EQ(dest_vec, std::vector<int>({3, 4, 5, 6})) << "Test: " << this->container_name();
    EXPECT_EQ(source_vec, std::vector<int>({1, 2, 7, 8})) << "Test: " << this->container_name();
}
