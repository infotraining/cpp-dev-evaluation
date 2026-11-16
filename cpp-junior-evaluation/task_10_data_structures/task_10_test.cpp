#include <gtest/gtest.h>

#ifdef USE_SOLUTION
#include "task_10_solution.hpp"
#else
#include "task_10_starter.hpp"
#endif

TEST(DataStructuresTest, ReversesLinkedListInPlace) {
    ListNode n3(3);
    ListNode n2(2, &n3);
    ListNode n1(1, &n2);

    ListNode* newHead = reverse_list(&n1);
    ASSERT_EQ(newHead, &n3);
    EXPECT_EQ(newHead->next, &n2);
    EXPECT_EQ(newHead->next->next, &n1);
    EXPECT_EQ(n1.next, nullptr);
    EXPECT_EQ(reverse_list(nullptr), nullptr);
}

TEST(DataStructuresTest, ValidatesBracketsWithStack) {
    EXPECT_TRUE(are_brackets_balanced("{[()]}"));
    EXPECT_TRUE(are_brackets_balanced("a + (b * [c - d])"));
    EXPECT_FALSE(are_brackets_balanced("{[(])}"));
    EXPECT_FALSE(are_brackets_balanced("((("));
    EXPECT_FALSE(are_brackets_balanced(")"));
}
