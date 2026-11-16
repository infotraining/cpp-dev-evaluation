#include "solution.hpp"
#include <algorithm>

void removeEvenNumbers(std::vector<int>& vec) {
    vec.erase(
        std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }),
        vec.end()
    );
}

std::unordered_map<std::string, int> countWordFrequencies(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> freq;
    for (const auto& word : words) {
        ++freq[word];
    }
    return freq;
}
