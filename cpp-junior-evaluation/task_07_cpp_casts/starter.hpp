#pragma once
#include <vector>

class Employee {
public:
    virtual ~Employee() = default;
};

class Developer : public Employee {};
class Manager : public Employee {};

void legacyPrint(char* str);

int countDevelopers(const std::vector<Employee*>& staff);
int truncateToInt(double value);
void callLegacyApi(const char* text);
