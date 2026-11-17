#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

namespace Solution
{
    class PacketBuffer
    {
    public:
        explicit PacketBuffer(size_t size);
        size_t size() const;
        std::unique_ptr<uint8_t[]> release_buffer();

    private:
        std::unique_ptr<uint8_t[]> data_;
        size_t size_;
    };

    struct NodeB;

    struct NodeA
    {
        std::shared_ptr<NodeB> next;
    };

    struct NodeB
    {
        std::weak_ptr<NodeA> prev;
        bool has_valid_prev() const;
    };
} // namespace Solution
