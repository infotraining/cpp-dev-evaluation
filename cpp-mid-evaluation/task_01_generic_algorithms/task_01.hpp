#pragma once

#include <functional>
#include <type_traits>
#include <vector>
#include <string>

template <typename T>
class ValueSeries
{
public:
    ValueSeries();
    void add(T value);
    const std::vector<T>& values() const;
    std::size_t size() const;

private:
    std::vector<T> values_;
};

template <typename T, typename Predicate, typename Transform>
auto filter_transform(const std::vector<T>& input, Predicate predicate, Transform transform)
    -> std::vector<std::remove_cvref_t<std::invoke_result_t<Transform, const T&>>>
{
    using Result = std::remove_cvref_t<std::invoke_result_t<Transform, const T&>>;
    std::vector<Result> output;
    for (const T& value : input)
    {
        if (std::invoke(predicate, value))
        {
            output.push_back(std::invoke(transform, value));
        }
    }
    return output;
}

extern template class ValueSeries<int>;
extern template class ValueSeries<double>;
extern template class ValueSeries<std::string>;
