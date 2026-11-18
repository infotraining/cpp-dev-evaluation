#include "task_09.hpp"

LeafTask::LeafTask(int effort)
    : effort_(effort)
{
}

int LeafTask::effort() const
{
    return effort_;
}

std::unique_ptr<WorkItem> LeafTask::clone() const
{
    return {};
}

void TaskGroup::add(std::unique_ptr<WorkItem> item)
{
    (void)item;
}

int TaskGroup::effort() const
{
    return 0;
}

std::unique_ptr<WorkItem> TaskGroup::clone() const
{
    return {};
}

std::size_t TaskGroup::child_count() const
{
    return children_.size();
}
