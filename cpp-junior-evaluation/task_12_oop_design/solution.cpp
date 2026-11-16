#include "solution.hpp"
#include <stdexcept>

SimpleDate::SimpleDate(int day, int month, int year) {
    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::invalid_argument("Invalid date values");
    }
    day_ = day;
    month_ = month;
    year_ = year;
}

void SimpleDate::setMonth(int month) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month");
    }
    month_ = month;
}

NotificationService::NotificationService(ILogger& logger) : logger_(logger) {}

void NotificationService::sendAlert(const std::string& user) {
    logger_.log("Alert sent to: " + user);
}
