#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <iterator>

namespace Solution
{

    void remove_even_numbers(std::vector<int>& vec);
    std::unordered_map<std::string, int> count_word_frequencies(const std::vector<std::string>& words);

    template <std::ranges::range TSource, std::ranges::range TDest, std::totally_ordered TValue>
    void move_chunk_of_container_to(TSource& source, TDest& destination, const TValue& value_from, const TValue& value_to)
    {
        assert(std::is_sorted(source.begin(), source.end())); // precondition: source must be sorted

        if constexpr (std::ranges::random_access_range<TSource>)
        {
            auto it_from = std::lower_bound(source.begin(), source.end(), value_from);
            auto it_to = std::upper_bound(source.begin(), source.end(), value_to);

            // Only call reserve if the destination supports it
            if constexpr (requires { destination.reserve(size_t{}); })
            {
                destination.reserve(destination.size() + std::distance(it_from, it_to));
            }
            std::move(it_from, it_to, std::back_inserter(destination));
            source.erase(it_from, it_to);
        }
        else if constexpr (std::same_as<TSource, std::list<typename TSource::value_type>> && std::same_as<TSource, TDest>)
        {
            auto it_from = std::find_if(source.begin(), source.end(), [&](const auto& val) { return val >= value_from; });
            auto it_to = std::find_if(source.begin(), source.end(), [&](const auto& val) { return val > value_to; });

            destination.splice(destination.end(), source, it_from, it_to);
        }
        else
        {
            auto it_from = std::find_if(source.begin(), source.end(), [&](const auto& val) { return val >= value_from; });
            auto it_to = std::find_if(source.begin(), source.end(), [&](const auto& val) { return val > value_to; });

            std::move(it_from, it_to, std::back_inserter(destination));
            source.erase(it_from, it_to);
        }
    }

} // namespace Solution
