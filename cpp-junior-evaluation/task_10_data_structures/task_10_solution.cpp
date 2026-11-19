#include "task_10_solution.hpp"

#include <stack>

namespace Solution
{
    bool are_brackets_balanced(const std::string& expr)
    {
        std::stack<char> st;
        for (char ch : expr)
        {
            if (ch == '(' || ch == '{' || ch == '[')
            {
                st.push(ch);
            }
            else if (ch == ')' || ch == '}' || ch == ']')
            {
                if (st.empty())
                {
                    return false;
                }
                char top = st.top();
                st.pop();
                if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '['))
                {
                    return false;
                }
            }
        }
        return st.empty();
    }
} // namespace Solution