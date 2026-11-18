#pragma once

#include <sstream>
#include <string>

namespace mid
{
    template <typename T>
    std::string format_value(const T& value)
    {
        std::ostringstream stream;
        stream << value;
        return stream.str();
    }

    template <typename T>
    std::string format(const T& value)
    {
        return format_value(value);
    }
} // namespace mid

namespace geometry
{
    struct Point
    {
        int x{};
        int y{};
    };

    inline std::string format_value(const Point& point)
    {
        return "(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
    }
} // namespace geometry
