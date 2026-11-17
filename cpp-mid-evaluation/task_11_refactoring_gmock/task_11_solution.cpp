#include "task_11_solution.hpp"

namespace Solution
{
    OrderProcessor::OrderProcessor(InventoryService& inventory, NotificationService& notifier)
        : inventory_(inventory)
        , notifier_(notifier)
    {
    }

    bool OrderProcessor::process(const Order& order)
    {
        if (order.quantity <= 0 || !inventory_.reserve(order.item, order.quantity))
        {
            return false;
        }
        notifier_.order_confirmed(order);
        return true;
    }
} // namespace Solution
