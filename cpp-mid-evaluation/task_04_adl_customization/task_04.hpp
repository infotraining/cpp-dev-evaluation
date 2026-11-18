#pragma once

#include <sstream>
#include <string>

namespace mid
{
    template <typename T>
    std::string format_value(const T& value)
    {
        std::ostringstream stream;
        (void)value;
        if constexpr (requires { stream << value; })
        {
            stream << value;
            return stream.str();
        }
        return {};
    }

    template <typename T>
    std::string format(const T& value)
    {
        // TODO: Call format_value unqualified so ADL can find customizations.
        (void)value;
        return {};
    }
} // namespace mid

namespace geometry
{
    struct Point
    {
        int x{};
        int y{};
    };
} // namespace geometry
