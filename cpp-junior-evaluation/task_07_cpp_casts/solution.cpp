#include "solution.hpp"

void legacyPrint(char* str) {
    (void)str;
}

int countDevelopers(const std::vector<Employee*>& staff) {
    int count = 0;
    for (Employee* emp : staff) {
        if (dynamic_cast<Developer*>(emp) != nullptr) {
            ++count;
        }
    }
    return count;
}

int truncateToInt(double value) {
    return static_cast<int>(value);
}

void callLegacyApi(const char* text) {
    legacyPrint(const_cast<char*>(text));
}
