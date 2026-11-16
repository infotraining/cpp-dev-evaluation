#pragma once

namespace Solution
{
    class ScopeFlagGuard
    {
    public:
        explicit ScopeFlagGuard(bool& flag);
        ~ScopeFlagGuard();

        ScopeFlagGuard(const ScopeFlagGuard&) = delete;
        ScopeFlagGuard& operator=(const ScopeFlagGuard&) = delete;
        ScopeFlagGuard(ScopeFlagGuard&&) = delete;
        ScopeFlagGuard& operator=(ScopeFlagGuard&&) = delete;

    private:
        bool& flag_;
    };

    void execute_with_guard(bool& activeFlag, bool shouldThrow);
} // namespace Solution
