#include "task_09_solution.hpp"

#include <numeric>
#include <stdexcept>
#include <utility>

namespace Solution
{
    LeafTask::LeafTask(int effort)
        : effort_(effort)
    {
        if (effort_ < 0)
        {
            throw std::invalid_argument("effort must not be negative");
        }
    }

    int LeafTask::effort() const
    {
        return effort_;
    }

    std::unique_ptr<WorkItem> LeafTask::clone() const
    {
        return std::make_unique<LeafTask>(*this);
    }

    void TaskGroup::add(std::unique_ptr<WorkItem> item)
    {
        if (!item)
        {
            throw std::invalid_argument("task group cannot own a null item");
        }
        children_.push_back(std::move(item));
    }

    int TaskGroup::effort() const
    {
        return std::accumulate(children_.begin(), children_.end(), 0,
            [](int total, const auto& child) { return total + child->effort(); });
    }

    std::unique_ptr<WorkItem> TaskGroup::clone() const
    {
        auto copy = std::make_unique<TaskGroup>();
        for (const auto& child : children_)
        {
            copy->add(child->clone());
        }
        return copy;
    }

    std::size_t TaskGroup::child_count() const
    {
        return children_.size();
    }
} // namespace Solution
