#pragma once
#include <cstddef>

class IntArray {
public:
    explicit IntArray(size_t size);
    ~IntArray();

    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);

    IntArray(IntArray&& other) noexcept;
    IntArray& operator=(IntArray&& other) noexcept;

    size_t size() const { return size_; }
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    bool operator==(const IntArray& other) const;

private:
    size_t size_;
    int* data_;
};
