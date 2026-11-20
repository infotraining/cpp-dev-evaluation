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

        bool operator==(const ScoredItem& other) const = default;
        auto operator<=>(const ScoredItem& other) const = default;
    };

    std::vector<std::string> build_report(const std::vector<ScoredItem>& items, int minimum_score);

    const ScoredItem* find_item_by_id(const std::vector<ScoredItem>& items, int id);
    
    std::vector<ScoredItem> get_top_n(const std::vector<ScoredItem>& items, std::size_t n);
} // namespace Solution
