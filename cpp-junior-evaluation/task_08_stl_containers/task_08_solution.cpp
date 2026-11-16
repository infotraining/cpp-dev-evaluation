#include "task_08_solution.hpp"
#include <algorithm>

void remove_even_numbers(std::vector<int>& vec) {
    vec.erase(
        std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }),
        vec.end()
    );
}

std::unordered_map<std::string, int> count_word_frequencies(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> freq;
    for (const auto& word : words) {
        ++freq[word];
    }
    return freq;
}
