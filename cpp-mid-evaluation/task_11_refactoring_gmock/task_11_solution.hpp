#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Solution
{
    struct Order
    {
        std::string customer_email;
        std::string customer_type;
        std::string item;
        int quantity{};
        int unit_price_cents{};
        std::string payment_method;
    };

    enum class OrderStatus
    {
        Confirmed,
        InvalidOrder,
        OutOfStock,
        PaymentFailed
    };

    class InventoryService
    {
    public:
        virtual ~InventoryService() = default;
        virtual bool reserve(const std::string& item, int quantity) = 0;
        virtual void release(const std::string& item, int quantity) = 0;
    };

    class PaymentGateway
    {
    public:
        virtual ~PaymentGateway() = default;
        virtual bool charge(const std::string& method, long long amount_cents) = 0;
    };

    class NotificationService
    {
    public:
        virtual ~NotificationService() = default;
        virtual void order_confirmed(const Order& order) = 0;
    };

    class Logger
    {
    public:
        virtual ~Logger() = default;
        virtual void log(const std::string& message) = 0;
    };

    // Open for extension: new customer types are new policies, not edits to OrderProcessor.
    class DiscountPolicy
    {
    public:
        virtual ~DiscountPolicy() = default;
        virtual long long apply(long long total_cents) const = 0;
    };

    class PercentageDiscount : public DiscountPolicy
    {
    public:
        explicit PercentageDiscount(int percent)
            : percent_(percent)
        {
        }
        long long apply(long long total_cents) const override { return total_cents * (100 - percent_) / 100; }

    private:
        int percent_;
    };

    class OrderProcessor
    {
    public:
        OrderProcessor(InventoryService& inventory, PaymentGateway& payments, NotificationService& notifier,
            Logger& logger, const DiscountPolicy& discount);
        OrderStatus process(const Order& order);

    private:
        InventoryService& inventory_;
        PaymentGateway& payments_;
        NotificationService& notifier_;
        Logger& logger_;
        const DiscountPolicy& discount_;
    };
} // namespace Solution
