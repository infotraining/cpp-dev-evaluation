#include "task_04_solution.hpp"

#include <utility>

UserProfile create_profile(std::string username, std::vector<int> scores)
{
    return UserProfile{std::move(username), std::move(scores)};
}

ValueCategory classify_value_category(int& x)
{
    (void)x;
    return ValueCategory::LValue;
}

ValueCategory classify_value_category(int&& x)
{
    (void)x;
    return ValueCategory::RValue;
}

ValueCategory perfect_forward_test(int& x)
{
    return classify_value_category(x);
}

ValueCategory perfect_forward_test(int&& x)
{
    return classify_value_category(std::move(x));
}
