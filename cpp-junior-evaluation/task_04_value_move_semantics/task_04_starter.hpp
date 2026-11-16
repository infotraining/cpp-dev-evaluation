#pragma once
#include <string>
#include <vector>

struct UserProfile {
    std::string username;
    std::vector<int> scores;
};

UserProfile create_profile(std::string username, std::vector<int> scores);

int classify_value_category(int& x);
int classify_value_category(int&& x);
int forward_test();
