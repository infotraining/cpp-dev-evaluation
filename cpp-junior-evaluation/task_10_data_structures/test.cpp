#include <gtest/gtest.h>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(DataStructuresTest, ReversesLinkedListInPlace) {
    ListNode n3(3);
    ListNode n2(2, &n3);
    ListNode n1(1, &n2);

    ListNode* newHead = reverseList(&n1);
    ASSERT_EQ(newHead, &n3);
    EXPECT_EQ(newHead->next, &n2);
    EXPECT_EQ(newHead->next->next, &n1);
    EXPECT_EQ(n1.next, nullptr);
    EXPECT_EQ(reverseList(nullptr), nullptr);
}

TEST(DataStructuresTest, ValidatesBracketsWithStack) {
    EXPECT_TRUE(areBracketsBalanced("{[()]}"));
    EXPECT_TRUE(areBracketsBalanced("a + (b * [c - d])"));
    EXPECT_FALSE(areBracketsBalanced("{[(])}"));
    EXPECT_FALSE(areBracketsBalanced("((("));
    EXPECT_FALSE(areBracketsBalanced(")"));
}
