#pragma once

#include <string>
#include <type_traits>
#include <utility>

template <typename T>
struct is_supported_value : std::false_type
{
};

template <typename T>
inline constexpr bool is_supported_value_v = is_supported_value<std::remove_cvref_t<T>>::value;

///////////////////////////////////////////////////////

template <typename T>
struct ValueBox
{
    T value;
};

template <typename T>
ValueBox(T) -> ValueBox<T>;
ValueBox(const char*) -> ValueBox<std::string>;

///////////////////////////////////////////////////////

template <typename T>
std::string format_value(const T& value)
{
    (void)value;
    return {};
}
