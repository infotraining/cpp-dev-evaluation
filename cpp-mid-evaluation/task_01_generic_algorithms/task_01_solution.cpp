#include "task_01_solution.hpp"

namespace Solution
{
    template <typename T>
    ValueSeries<T>::ValueSeries() = default;

    template <typename T>
    void ValueSeries<T>::add(T value)
    {
        values_.push_back(std::move(value));
    }

    template <typename T>
    const std::vector<T> &ValueSeries<T>::values() const
    {
        return values_;
    }

    template <typename T>
    std::size_t ValueSeries<T>::size() const
    {
        return values_.size();
    }

    template class ValueSeries<int>;
    template class ValueSeries<double>;
    template class ValueSeries<std::string>;
}
