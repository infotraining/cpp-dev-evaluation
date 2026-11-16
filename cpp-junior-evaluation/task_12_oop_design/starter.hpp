#pragma once
#include <string>

class SimpleDate {
public:
    SimpleDate(int day, int month, int year);
    void setMonth(int month);

    int day() const { return day_; }
    int month() const { return month_; }
    int year() const { return year_; }

private:
    int day_;
    int month_;
    int year_;
};

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& msg) = 0;
};

class NotificationService {
public:
    explicit NotificationService(ILogger& logger);
    void sendAlert(const std::string& user);

private:
    ILogger& logger_;
};
