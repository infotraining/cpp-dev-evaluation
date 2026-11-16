#pragma once
#include <string>

namespace Solution
{
    struct ListNode
    {
        int val;
        ListNode* next;
        explicit ListNode(int v, ListNode* n = nullptr)
            : val(v)
            , next(n)
        { }
    };

    ListNode* reverse_list(ListNode* head);
    bool are_brackets_balanced(const std::string& expr);

} // namespace Solution
