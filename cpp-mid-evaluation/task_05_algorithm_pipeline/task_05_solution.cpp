#include "task_05_solution.hpp"

#include <algorithm>
#include <iterator>

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
} // namespace Solution
