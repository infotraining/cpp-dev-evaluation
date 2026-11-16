#include "task_02_solution.hpp"
#include <utility>

PacketBuffer::PacketBuffer(size_t size)
    : data_(std::make_unique<uint8_t[]>(size)), size_(size) {}

size_t PacketBuffer::size() const {
    return size_;
}

std::unique_ptr<uint8_t[]> PacketBuffer::release_buffer() {
    size_ = 0;
    return std::move(data_);
}

bool NodeB::has_valid_prev() const {
    return !prev.expired();
}
