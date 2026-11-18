#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <set>

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

    //-----------------------------------------------

    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void update(int value) = 0;
    };

    class Subject
    {
    protected:
        void notify(int value)
        {
            for (auto it = observers_.begin(); it != observers_.end();)
            {
                if (auto obs = it->lock())
                {
                    obs->update(value);
                    ++it;
                }
                else
                {
                    it = observers_.erase(it);
                }
            }
        }

    public:
        void attach(std::shared_ptr<Observer> observer)
        {
            observers_.insert(observer);
        }

        void detach(std::shared_ptr<Observer> observer)
        {
            observers_.erase(observer);
        }

    private:
        std::set<std::weak_ptr<Observer>, std::owner_less<std::weak_ptr<Observer>>> observers_;
    };

    class TemperatureSensor : public Subject
    {
    public:
        void set_temperature(int value)
        {
            notify(value);
        }
    };
} // namespace Solution
