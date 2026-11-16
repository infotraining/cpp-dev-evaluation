#include "solution.hpp"
#include <utility>

UserProfile createProfile(std::string username, std::vector<int> scores) {
    return UserProfile{std::move(username), std::move(scores)};
}

int classifyValueCategory(int& x) {
    (void)x;
    return 1;
}

int classifyValueCategory(int&& x) {
    (void)x;
    return 2;
}

int forwardTest() {
    int&& rref = 42;
    return classifyValueCategory(rref);
}
