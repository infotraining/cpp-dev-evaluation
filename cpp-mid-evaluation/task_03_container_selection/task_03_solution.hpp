#pragma once

#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Solution
{
struct Event
{
    int id{};
    std::string message;
};

class EventCatalog
{
public:
    void add(Event event);
    std::optional<Event> process_oldest();
    std::optional<Event> find(int id) const;
    std::vector<Event> snapshot_sorted() const;

private:
    std::deque<int> pending_ids_;
    std::unordered_map<int, Event> events_;
};
}
