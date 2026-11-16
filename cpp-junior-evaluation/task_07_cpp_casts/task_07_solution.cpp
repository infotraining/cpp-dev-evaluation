#include "task_07_solution.hpp"

namespace Solution
{
    void legacy_print(char* str)
    {
        (void)str;
    }

    int count_developers(const std::vector<Employee*>& staff)
    {
        int count = 0;
        for (Employee* emp : staff)
        {
            if (dynamic_cast<Developer*>(emp) != nullptr)
            {
                ++count;
            }
        }
        return count;
    }

    int truncate_to_int(double value)
    {
        return static_cast<int>(value);
    }

    void call_legacy_api(const char* text)
    {
        legacy_print(const_cast<char*>(text));
    }
} // namespace Solution