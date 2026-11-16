#include "task_06_solution.hpp"
#include <algorithm>
#include <iterator>
#include <utility>

std::vector<int> filter_above_threshold(const std::vector<int>& data, int threshold) {
    std::vector<int> result;
    std::copy_if(data.begin(), data.end(), std::back_inserter(result),
                 [threshold](int val) { return val > threshold; });
    return result;
}

void EventDispatcher::subscribe(std::function<void(int)> callback) {
    if (callback) {
        listeners_.push_back(std::move(callback));
    }
}

void EventDispatcher::emit(int eventCode) const {
    for (const auto& listener : listeners_) {
        if (listener) {
            listener(eventCode);
        }
    }
}
