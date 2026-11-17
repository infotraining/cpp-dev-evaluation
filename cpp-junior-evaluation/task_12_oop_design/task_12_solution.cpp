#include "task_12_solution.hpp"

#include <stdexcept>

namespace Solution
{

    SimpleDate::SimpleDate(int day, int month, int year)
    {
        if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
        {
            throw std::invalid_argument("Invalid date values");
        }
        day_ = day;
        month_ = month;
        year_ = year;
    }

    void SimpleDate::set_month(int month)
    {
        if (month < 1 || month > 12)
        {
            throw std::invalid_argument("Invalid month");
        }
        month_ = month;
    }

    NotificationService::NotificationService(ILogger& logger)
        : logger_(logger)
    { }

    void NotificationService::send_alert(const std::string& user)
    {
        logger_.log("Alert sent to: " + user);
    }

} // namespace Solution