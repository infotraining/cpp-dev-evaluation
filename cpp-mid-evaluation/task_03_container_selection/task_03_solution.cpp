#include "task_03_solution.hpp"

#include <algorithm>

namespace Solution
{
void EventCatalog::add(Event event)
{
    const int id = event.id;
    const auto iterator = events_.find(id);
    if (iterator == events_.end())
    {
        events_.emplace(id, std::move(event));
        pending_ids_.push_back(id);
    }
    else
    {
        iterator->second = std::move(event);
    }
}

std::optional<Event> EventCatalog::process_oldest()
{
    if (pending_ids_.empty())
    {
        return std::nullopt;
    }
    const int id = pending_ids_.front();
    pending_ids_.pop_front();
    const auto iterator = events_.find(id);
    if (iterator == events_.end())
    {
        return std::nullopt;
    }
    Event event = std::move(iterator->second);
    events_.erase(iterator);
    return event;
}

std::optional<Event> EventCatalog::find(int id) const
{
    const auto iterator = events_.find(id);
    if (iterator == events_.end())
    {
        return std::nullopt;
    }
    return iterator->second;
}

std::vector<Event> EventCatalog::snapshot_sorted() const
{
    std::vector<Event> snapshot;
    snapshot.reserve(events_.size());
    for (const auto& [id, event] : events_)
    {
        (void)id;
        snapshot.push_back(event);
    }
    std::ranges::sort(snapshot, {}, &Event::id);
    return snapshot;
}
}
