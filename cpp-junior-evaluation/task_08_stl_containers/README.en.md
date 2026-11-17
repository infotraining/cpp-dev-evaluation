# Task 8: STL Containers and Iterator Safety

## Objective

1. Implement function `void remove_even_numbers(std::vector<int>& vec)`:
   - Safely removes all even numbers from the vector
   - Avoids iterator invalidation (use erase-remove idiom or loop with `it = vec.erase(it)`)

2. Implement function `std::unordered_map<std::string, int> count_word_frequencies(const std::vector<std::string>& words)`:
   - Counts the number of occurrences of each word

## Implementation Requirements

- Properly handle iterator invalidation when modifying containers
- Use efficient container operations
- Apply STL idioms correctly

## Evaluation Criteria (0-3 points)

- **0 points:** Iterator invalidation error (undefined behavior when iterating and removing from vector)
- **1 point:** Correct word counting, but suboptimal or incorrect vector removal
- **2 points:** Both tasks correct using loops
- **3 points:** Idiomatic use of `std::remove_if` + `erase` and `std::unordered_map` with `operator[]`
