#include "task_03_solution.hpp"

#include <algorithm>

namespace Solution
{

    IntArray::IntArray(size_t size)
        : size_(size)
        , data_(size > 0 ? new int[size]{} : nullptr)
    { }

    IntArray::~IntArray()
    {
        delete[] data_;
    }

    IntArray::IntArray(const IntArray& other)
        : size_(other.size_)
        , data_(other.size_ > 0 ? new int[other.size_] : nullptr)
    {
        if (data_)
        {
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    IntArray& IntArray::operator=(const IntArray& other)
    {
        if (this == &other)
        {
            return *this;
        }

        int* new_data = other.size_ > 0 ? new int[other.size_] : nullptr;
        if (new_data)
        {
            std::copy(other.data_, other.data_ + other.size_, new_data);
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        return *this;
    }

    IntArray::IntArray(IntArray&& other) noexcept
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    IntArray& IntArray::operator=(IntArray&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        data_ = other.data_;
        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }

    void IntArray::swap(IntArray& other) noexcept
    {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    int& IntArray::operator[](size_t index)
    {
        return data_[index];
    }

    const int& IntArray::operator[](size_t index) const
    {
        return data_[index];
    }

    bool IntArray::operator==(const IntArray& other) const
    {
        if (size_ != other.size_)
        {
            return false;
        }
        return std::equal(data_, data_ + size_, other.data_);
    }

} // namespace Solution