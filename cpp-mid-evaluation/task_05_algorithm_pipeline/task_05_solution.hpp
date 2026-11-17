#pragma once

#include <string>
#include <vector>

namespace Solution
{
    struct ScoredItem
    {
        int id{};
        int score{};
        std::string name;
    };

    std::vector<std::string> build_report(const std::vector<ScoredItem>& items, int minimum_score);
    const ScoredItem* find_item_by_id(const std::vector<ScoredItem>& items, int id);
} // namespace Solution
