#include "task_11_solution.hpp"

namespace Solution
{
    OrderProcessor::OrderProcessor(InventoryService& inventory, PaymentGateway& payments,
        NotificationService& notifier, Logger& logger, const DiscountPolicy& discount)
        : inventory_(inventory)
        , payments_(payments)
        , notifier_(notifier)
        , logger_(logger)
        , discount_(discount)
    {
    }

    OrderStatus OrderProcessor::process(const Order& order)
    {
        if (order.quantity <= 0 || order.unit_price_cents < 0 || order.customer_email.empty())
        {
            logger_.log("invalid order");
            return OrderStatus::InvalidOrder;
        }

        const long long total = discount_.apply(static_cast<long long>(order.quantity) * order.unit_price_cents);

        if (!inventory_.reserve(order.item, order.quantity))
        {
            logger_.log("out of stock: " + order.item);
            return OrderStatus::OutOfStock;
        }

        if (!payments_.charge(order.payment_method, total))
        {
            inventory_.release(order.item, order.quantity);
            logger_.log("payment failed");
            return OrderStatus::PaymentFailed;
        }

        notifier_.order_confirmed(order);
        logger_.log("order confirmed");
        return OrderStatus::Confirmed;
    }
} // namespace Solution
