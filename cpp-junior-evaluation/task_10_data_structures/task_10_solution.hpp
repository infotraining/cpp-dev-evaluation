#pragma once
#include <string>
#include <cassert>

namespace Solution
{
    class LinkedList
    {
        struct Node
        {
            int value;
            Node* next;
            Node(int val)
                : value(val)
                , next(nullptr)
            { }
        };

        Node* head_ = nullptr;
        Node* tail_ = nullptr;
        int list_size_ = 0;

    public:
        LinkedList() = default;

        LinkedList(std::initializer_list<int> init)
        {
            for (int val : init)
                push_back(val);
        }

        LinkedList(const LinkedList& other)
        {
            Node* current = other.head_;
            while (current)
            {
                push_back(current->value);
                current = current->next;
            }
        }

        LinkedList& operator=(const LinkedList& other)
        {
            if (this != &other)
            {
                LinkedList temp(other);
                swap(temp);
            }
            return *this;
        }

        LinkedList(LinkedList&& other) noexcept
            : head_(other.head_)
            , tail_(other.tail_)
            , list_size_(other.list_size_)
        {
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.list_size_ = 0;
        }

        LinkedList& operator=(LinkedList&& other) noexcept
        {
            if (this != &other)
            {
                LinkedList temp(std::move(other));
                swap(temp);
            }
            return *this;
        }

        ~LinkedList() noexcept
        {
            while (!is_empty())
                pop_back();
        }

        bool is_empty() const noexcept { return list_size_ == 0; }

        int size() const noexcept { return list_size_; }

        int front() const { return head_->value; }

        int back() const { return tail_->value; }

        void push_back(int val)
        {
            Node* new_node = new Node(val);
            if (is_empty())
            {
                head_ = tail_ = new_node;
            }
            else
            {
                tail_->next = new_node;
                tail_ = new_node;
            }
            ++list_size_;
        }

        void pop_back() noexcept
        {
            assert(!is_empty());

            if (head_ == tail_)
            {
                delete head_;
                head_ = tail_ = nullptr;
            }
            else
            {
                Node* current = head_;
                while (current->next != tail_)
                    current = current->next;
                delete tail_;
                tail_ = current;
                tail_->next = nullptr;
            }
            --list_size_;
        }

        bool operator==(const LinkedList& other) const noexcept
        {
            if (list_size_ != other.list_size_)
                return false;

            Node* current1 = head_;
            Node* current2 = other.head_;
            while (current1 && current2)
            {
                if (current1->value != current2->value)
                    return false;
                current1 = current1->next;
                current2 = current2->next;
            }
            return true;
        }

        bool operator!=(const LinkedList& other) const noexcept
        {
            return !(*this == other);
        }

        void swap(LinkedList& other) noexcept
        {
            std::swap(head_, other.head_);
            std::swap(tail_, other.tail_);
            std::swap(list_size_, other.list_size_);
        }
    };

    bool are_brackets_balanced(const std::string& expr);

} // namespace Solution
