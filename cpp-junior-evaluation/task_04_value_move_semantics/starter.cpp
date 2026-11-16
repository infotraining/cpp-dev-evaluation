#include "starter.hpp"
#include <utility>

UserProfile createProfile(std::string username, std::vector<int> scores) {
    // TODO: Utwórz i zwróć UserProfile bez zbędnych kopii
    return UserProfile{};
}

int classifyValueCategory(int& x) {
    (void)x;
    return 0;
}

int classifyValueCategory(int&& x) {
    (void)x;
    return 0;
}

int forwardTest() {
    int&& rref = 42;
    return classifyValueCategory(rref);
}
