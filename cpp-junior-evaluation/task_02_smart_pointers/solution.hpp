#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

class PacketBuffer {
public:
    explicit PacketBuffer(size_t size);
    size_t size() const;
    std::unique_ptr<uint8_t[]> releaseBuffer();

private:
    std::unique_ptr<uint8_t[]> data_;
    size_t size_;
};

struct NodeB;

struct NodeA {
    std::shared_ptr<NodeB> next;
};

struct NodeB {
    std::weak_ptr<NodeA> prev;
    bool hasValidPrev() const;
};
