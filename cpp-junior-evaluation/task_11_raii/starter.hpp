#pragma once

class ScopeFlagGuard {
public:
    explicit ScopeFlagGuard(bool& flag);
    ~ScopeFlagGuard();

    // TODO: Zablokuj kopiowanie i przenoszenie

private:
    bool& flag_;
};

void executeWithGuard(bool& activeFlag, bool shouldThrow);
