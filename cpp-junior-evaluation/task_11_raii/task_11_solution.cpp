#include "task_11_solution.hpp"

#include <stdexcept>

namespace Solution
{
    ScopeFlagGuard::ScopeFlagGuard(bool& flag)
        : flag_(flag)
    {
        flag_ = true;
    }

    ScopeFlagGuard::~ScopeFlagGuard()
    {
        flag_ = false;
    }

    void execute_with_guard(bool& activeFlag, bool shouldThrow)
    {
        ScopeFlagGuard guard(activeFlag);
        if (shouldThrow)
        {
            throw std::runtime_error("Failure inside guarded scope");
        }
    }
} // namespace Solution
