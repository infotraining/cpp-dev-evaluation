#pragma once

#include <string>
#include <type_traits>

namespace Solution
{
template <typename T>
struct is_supported_value
    : std::bool_constant<std::is_arithmetic_v<std::remove_cvref_t<T>> ||
                         std::is_same_v<std::remove_cvref_t<T>, std::string>>
{
};

template <typename T>
inline constexpr bool is_supported_value_v = is_supported_value<T>::value;

template <typename T>
struct ValueBox
{
    T value;
};

template <typename T>
ValueBox(T) -> ValueBox<T>;
ValueBox(const char*) -> ValueBox<std::string>;

template <typename T>
std::string format_value(const T& value)
{
    using ValueType = std::remove_cvref_t<T>;
    static_assert(is_supported_value_v<ValueType>, "ValueBox supports arithmetic and string values only");
    if constexpr (std::is_arithmetic_v<ValueType>)
    {
        return std::to_string(value);
    }
    else
    {
        return value;
    }
}
}
