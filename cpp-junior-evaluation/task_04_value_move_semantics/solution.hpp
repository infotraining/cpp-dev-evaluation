#pragma once
#include <string>
#include <vector>

struct UserProfile {
    std::string username;
    std::vector<int> scores;
};

UserProfile createProfile(std::string username, std::vector<int> scores);

int classifyValueCategory(int& x);
int classifyValueCategory(int&& x);
int forwardTest();
