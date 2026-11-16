#include "task_03_starter.hpp"
#include <algorithm>

IntArray::IntArray(size_t size) : size_(size), data_(size > 0 ? new int[size]{} : nullptr) {}

IntArray::~IntArray() {
    delete[] data_;
}

int& IntArray::operator[](size_t index) {
    return data_[index];
}

const int& IntArray::operator[](size_t index) const {
    return data_[index];
}

bool IntArray::operator==(const IntArray& other) const {
    // TODO: Porównaj zawartość tablic
    return false;
}
