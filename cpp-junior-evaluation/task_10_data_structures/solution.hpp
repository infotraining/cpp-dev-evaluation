#pragma once
#include <string>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

ListNode* reverseList(ListNode* head);
bool areBracketsBalanced(const std::string& expr);
