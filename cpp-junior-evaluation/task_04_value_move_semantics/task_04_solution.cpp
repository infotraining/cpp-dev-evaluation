#include "task_04_solution.hpp"
#include <utility>

UserProfile create_profile(std::string username, std::vector<int> scores) {
    return UserProfile{std::move(username), std::move(scores)};
}

int classify_value_category(int& x) {
    (void)x;
    return 1;
}

int classify_value_category(int&& x) {
    (void)x;
    return 2;
}

int forward_test() {
    int&& rref = 42;
    return classify_value_category(rref);
}
