#include "task_04_starter.hpp"
#include <utility>

UserProfile create_profile(std::string username, std::vector<int> scores) {
    // TODO: Utwórz i zwróć UserProfile bez zbędnych kopii
    return UserProfile{};
}

int classify_value_category(int& x) {
    (void)x;
    return 0;
}

int classify_value_category(int&& x) {
    (void)x;
    return 0;
}

int forward_test() {
    int&& rref = 42;
    return classify_value_category(rref);
}
