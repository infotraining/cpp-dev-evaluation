#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#ifdef USE_SOLUTION
#include "task_09_solution.hpp"
using namespace Solution;
#else
#include "task_09.hpp"
#endif

TEST(CompositePrototypeTest, AggregatesNestedWorkItems)
{
    TaskGroup root;
    root.add(std::make_unique<LeafTask>(2));
    auto child = std::make_unique<TaskGroup>();
    child->add(std::make_unique<LeafTask>(3));
    child->add(std::make_unique<LeafTask>(5));
    root.add(std::move(child));
    EXPECT_EQ(root.effort(), 10);
    EXPECT_EQ(root.child_count(), 2u);
}

TEST(CompositePrototypeTest, ClonesIndependently)
{
#ifndef USE_SOLUTION
    GTEST_SKIP() << "Starter code has no clone implementation yet.";
#else
    TaskGroup original;
    original.add(std::make_unique<LeafTask>(4));
    auto clone = original.clone();
    ASSERT_EQ(clone->effort(), 4);
    auto* cloned_group = dynamic_cast<TaskGroup*>(clone.get());
    ASSERT_NE(cloned_group, nullptr);
    cloned_group->add(std::make_unique<LeafTask>(6));
    EXPECT_EQ(cloned_group->effort(), 10);
    EXPECT_EQ(original.effort(), 4);
#endif
}

TEST(CompositePrototypeTest, EmptyGroupHasZeroEffort)
{
    EXPECT_EQ(TaskGroup{}.effort(), 0);
}

TEST(CompositePrototypeTest, RejectsInvalidLeavesAndChildren)
{
#ifdef USE_SOLUTION
    EXPECT_THROW((LeafTask(-1)), std::invalid_argument);
    EXPECT_THROW((TaskGroup{}.add(nullptr)), std::invalid_argument);
#else
    GTEST_SKIP() << "Starter code has no validation yet.";
#endif
}
