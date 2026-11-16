#include "starter.hpp"
#include <stdexcept>

SimpleDate::SimpleDate(int day, int month, int year) : day_(day), month_(month), year_(year) {
    // TODO: Dodaj walidację niezmienników
}

void SimpleDate::setMonth(int month) {
    // TODO: Dodaj walidację miesiąca
    month_ = month;
}

NotificationService::NotificationService(ILogger& logger) : logger_(logger) {}

void NotificationService::sendAlert(const std::string& user) {
    // TODO: Zaloguj wysłanie alertu
    (void)user;
}
