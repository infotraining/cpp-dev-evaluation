#include "task_05_solution.hpp"

#include <algorithm>
#include <iterator>
#include <ranges>

namespace Solution
{
    std::vector<std::string> build_report(const std::vector<ScoredItem>& items, int minimum_score)
    {
        std::vector<ScoredItem> selected;
        std::ranges::copy_if(items, std::back_inserter(selected),
            [minimum_score](const ScoredItem& item) { return item.score >= minimum_score; });

        std::ranges::sort(selected, [](const ScoredItem& left, const ScoredItem& right) {
            if (left.score != right.score)
            {
                return left.score > right.score;
            }
            return left.id < right.id;
        });

        std::vector<std::string> report(selected.size());
        std::ranges::transform(selected, report.begin(), [](const ScoredItem& item) {
            return std::to_string(item.id) + ":" + item.name + "=" + std::to_string(item.score);
        });

        return report;
    }

    const ScoredItem* find_item_by_id(const std::vector<ScoredItem>& items, int id)
    {
        const auto iterator = std::ranges::find(items, id, &ScoredItem::id);
        return iterator == items.end() ? nullptr : &*iterator;
    }

    std::vector<ScoredItem> get_top_n(const std::vector<ScoredItem>& items, std::size_t n)
    {
        std::vector<const ScoredItem*> temp_items = 
            items 
            | std::views::transform([](const ScoredItem& item) { return &item; })
            | std::ranges::to<std::vector>();

        const std::size_t count = std::min(n, temp_items.size());

        std::ranges::nth_element(temp_items, temp_items.begin() + count,
            [](const ScoredItem* left, const ScoredItem* right) {
                return *left < *right;
            });

        return temp_items | std::views::take(count) | std::views::transform([](const ScoredItem* item) { return *item; }) | std::ranges::to<std::vector>();
    }
} // namespace Solution
