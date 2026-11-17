#pragma once

#include <string>

struct Order
{
    std::string item;
    int quantity{};
    bool operator==(const Order&) const = default;
};

class InventoryService
{
public:
    virtual ~InventoryService() = default;
    virtual bool reserve(const std::string& item, int quantity) = 0;
};

class NotificationService
{
public:
    virtual ~NotificationService() = default;
    virtual void order_confirmed(const Order& order) = 0;
};

class OrderProcessor
{
public:
    OrderProcessor(InventoryService& inventory, NotificationService& notifier);
    bool process(const Order& order);

private:
    InventoryService& inventory_;
    NotificationService& notifier_;
};
