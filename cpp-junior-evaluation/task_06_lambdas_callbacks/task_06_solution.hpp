#pragma once
#include <functional>
#include <vector>

namespace Solution
{
    std::vector<int> filter_above_threshold(const std::vector<int>& data, int threshold);

    class EventDispatcher
    {
    public:
        void subscribe(std::function<void(int)> callback);
        void emit(int eventCode) const;

    private:
        std::vector<std::function<void(int)>> listeners_;
    };
} // namespace Solution