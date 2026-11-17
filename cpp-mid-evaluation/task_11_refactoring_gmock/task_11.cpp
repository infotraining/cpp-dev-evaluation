#include "task_11.hpp"

OrderProcessor::OrderProcessor(InventoryService& inventory, NotificationService& notifier)
    : inventory_(inventory)
    , notifier_(notifier)
{
}

bool OrderProcessor::process(const Order& order)
{
    (void)order;
    return false;
}
