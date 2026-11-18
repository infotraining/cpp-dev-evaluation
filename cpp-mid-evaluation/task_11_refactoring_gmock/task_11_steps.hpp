#pragma once

// Exemplary refactoring stages of the god class from task_11.hpp.
// Every step keeps the observable behavior and compiles on its own.
//
// How to find interfaces for dependencies (used in Step_2 -> Step_3):
//   1. Read process() and mark everything that is not pure logic: hidden state (stock map),
//      I/O (std::cout, std::clog), external systems (payment), policies (discount rules).
//   2. Group the marked lines by *reason to change* - each group is one responsibility (Step_1, Step_2).
//   3. Move each group into a class. Its public methods are exactly what OrderProcessor *uses*,
//      so the interface is shaped by the client's needs, not by the implementation (Step_2).
//   4. Extract an abstract class from those methods, name it by role (InventoryService, not StockMap),
//      and inject it by reference (Step_3). A mock now replaces the dependency in tests.
//   5. Where an if/else chain selects behavior by a string/type tag, turn the branches into
//      a strategy so new variants are added without editing OrderProcessor (Step_4).

#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

namespace Common
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
} // namespace Common

// Step 1: separate responsibilities *inside* the class (extract methods). Behavior and API untouched.
// process() now reads as a high-level algorithm; each private method is a candidate for extraction.
namespace Step_1
{
    using namespace Common;

    class OrderProcessor
    {
    public:
        OrderProcessor()
            : stock_{{"book", 10}, {"pen", 100}, {"laptop", 2}}
        {
        }

        OrderStatus process(const Order& order)
        {
            std::clog << "[LOG] processing order for " << order.customer_email << '\n';
            if (!is_valid(order))
                return OrderStatus::InvalidOrder;

            auto total = calculate_total(order);
            if (!total)
                return OrderStatus::InvalidOrder;

            if (!reserve(order.item, order.quantity))
                return OrderStatus::OutOfStock;

            if (!charge(order.payment_method, *total))
            {
                release(order.item, order.quantity);
                return OrderStatus::PaymentFailed;
            }

            notify(order);
            return OrderStatus::Confirmed;
        }

    private:
        static bool is_valid(const Order& order)
        {
            return order.quantity > 0 && order.unit_price_cents >= 0 && !order.customer_email.empty();
        }

        static std::optional<long long> calculate_total(const Order& order)
        {
            long long total = static_cast<long long>(order.quantity) * order.unit_price_cents;
            if (order.customer_type == "premium")
                return total * 90 / 100;
            if (order.customer_type == "vip")
                return total * 80 / 100;
            if (order.customer_type == "regular")
                return total;
            return std::nullopt;
        }

        bool reserve(const std::string& item, int quantity)
        {
            auto it = stock_.find(item);
            if (it == stock_.end() || it->second < quantity)
                return false;
            it->second -= quantity;
            return true;
        }

        void release(const std::string& item, int quantity) { stock_[item] += quantity; }

        static bool charge(const std::string& method, long long amount)
        {
            if (method == "card")
            {
                std::cout << "Charging card: " << amount << " cents\n";
                return amount <= 100000;
            }
            if (method == "paypal")
            {
                std::cout << "Charging PayPal: " << amount << " cents\n";
                return true;
            }
            return false;
        }

        static void notify(const Order& order)
        {
            std::cout << "Sending e-mail to " << order.customer_email << ": order of " << order.quantity << " x "
                      << order.item << " confirmed\n";
        }

        std::map<std::string, int> stock_;
    };
} // namespace Step_1

// Step 2: move every responsibility into its own *concrete* class. The public methods of these classes
// are exactly the calls OrderProcessor makes - this is the raw material of the future interfaces.
// OrderProcessor still creates the collaborators itself, so it is not testable in isolation yet.
namespace Step_2
{
    using namespace Common;

    class Inventory
    {
    public:
        bool reserve(const std::string& item, int quantity)
        {
            auto it = stock_.find(item);
            if (it == stock_.end() || it->second < quantity)
                return false;
            it->second -= quantity;
            return true;
        }
        void release(const std::string& item, int quantity) { stock_[item] += quantity; }

    private:
        std::map<std::string, int> stock_{{"book", 10}, {"pen", 100}, {"laptop", 2}};
    };

    class PaymentService
    {
    public:
        bool charge(const std::string& method, long long amount)
        {
            if (method == "card")
            {
                std::cout << "Charging card: " << amount << " cents\n";
                return amount <= 100000;
            }
            if (method == "paypal")
            {
                std::cout << "Charging PayPal: " << amount << " cents\n";
                return true;
            }
            return false;
        }
    };

    class EmailNotifier
    {
    public:
        void order_confirmed(const Order& order)
        {
            std::cout << "Sending e-mail to " << order.customer_email << ": order of " << order.quantity << " x "
                      << order.item << " confirmed\n";
        }
    };

    class ConsoleLogger
    {
    public:
        void log(const std::string& message) { std::clog << "[LOG] " << message << '\n'; }
    };

    class OrderProcessor
    {
    public:
        OrderStatus process(const Order& order)
        {
            logger_.log("processing order for " + order.customer_email);
            if (order.quantity <= 0 || order.unit_price_cents < 0 || order.customer_email.empty())
                return OrderStatus::InvalidOrder;

            long long total = static_cast<long long>(order.quantity) * order.unit_price_cents;
            if (order.customer_type == "premium")
                total = total * 90 / 100;
            else if (order.customer_type == "vip")
                total = total * 80 / 100;
            else if (order.customer_type != "regular")
                return OrderStatus::InvalidOrder;

            if (!inventory_.reserve(order.item, order.quantity))
                return OrderStatus::OutOfStock;

            if (!payments_.charge(order.payment_method, total))
            {
                inventory_.release(order.item, order.quantity);
                return OrderStatus::PaymentFailed;
            }

            notifier_.order_confirmed(order);
            return OrderStatus::Confirmed;
        }

    private:
        Inventory inventory_;
        PaymentService payments_;
        EmailNotifier notifier_;
        ConsoleLogger logger_;
    };
} // namespace Step_2

// Step 3: extract abstract interfaces from the Step_2 classes (same method set, role-based names),
// make the concrete classes implement them and inject them through the constructor.
// OrderProcessor depends on abstractions only -> it can be tested with mocks and stubs.
namespace Step_3
{
    using namespace Common;

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
        virtual bool charge(const std::string& method, long long amount) = 0;
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

    class InMemoryInventory : public InventoryService
    {
    public:
        bool reserve(const std::string& item, int quantity) override
        {
            auto it = stock_.find(item);
            if (it == stock_.end() || it->second < quantity)
                return false;
            it->second -= quantity;
            return true;
        }
        void release(const std::string& item, int quantity) override { stock_[item] += quantity; }

    private:
        std::map<std::string, int> stock_{{"book", 10}, {"pen", 100}, {"laptop", 2}};
    };

    class ConsolePayments : public PaymentGateway
    {
    public:
        bool charge(const std::string& method, long long amount) override
        {
            if (method == "card")
            {
                std::cout << "Charging card: " << amount << " cents\n";
                return amount <= 100000;
            }
            if (method == "paypal")
            {
                std::cout << "Charging PayPal: " << amount << " cents\n";
                return true;
            }
            return false;
        }
    };

    class ConsoleNotifier : public NotificationService
    {
    public:
        void order_confirmed(const Order& order) override
        {
            std::cout << "Sending e-mail to " << order.customer_email << ": order of " << order.quantity << " x "
                      << order.item << " confirmed\n";
        }
    };

    class ConsoleLogger : public Logger
    {
    public:
        void log(const std::string& message) override { std::clog << "[LOG] " << message << '\n'; }
    };

    class OrderProcessor
    {
    public:
        OrderProcessor(InventoryService& inventory, PaymentGateway& payments, NotificationService& notifier,
            Logger& logger)
            : inventory_(inventory)
            , payments_(payments)
            , notifier_(notifier)
            , logger_(logger)
        {
        }

        OrderStatus process(const Order& order)
        {
            logger_.log("processing order for " + order.customer_email);
            if (order.quantity <= 0 || order.unit_price_cents < 0 || order.customer_email.empty())
                return OrderStatus::InvalidOrder;

            // pricing is still an if/else chain - the remaining OCP violation, fixed in Step_4
            long long total = static_cast<long long>(order.quantity) * order.unit_price_cents;
            if (order.customer_type == "premium")
                total = total * 90 / 100;
            else if (order.customer_type == "vip")
                total = total * 80 / 100;
            else if (order.customer_type != "regular")
                return OrderStatus::InvalidOrder;

            if (!inventory_.reserve(order.item, order.quantity))
                return OrderStatus::OutOfStock;

            if (!payments_.charge(order.payment_method, total))
            {
                inventory_.release(order.item, order.quantity);
                return OrderStatus::PaymentFailed;
            }

            notifier_.order_confirmed(order);
            return OrderStatus::Confirmed;
        }

    private:
        InventoryService& inventory_;
        PaymentGateway& payments_;
        NotificationService& notifier_;
        Logger& logger_;
    };
} // namespace Step_3

// Step 4: the last "policy" dependency - pricing - becomes a strategy. New customer types are
// registered, not coded into OrderProcessor (OCP). The service interfaces are reused from Step_3.
namespace Step_4
{
    using namespace Common;
    using Step_3::InventoryService;
    using Step_3::Logger;
    using Step_3::NotificationService;
    using Step_3::PaymentGateway;

    class PricingPolicy
    {
    public:
        virtual ~PricingPolicy() = default;
        // std::nullopt means: the customer type is not supported
        virtual std::optional<long long> total_for(const Order& order) const = 0;
    };

    class TieredPricing : public PricingPolicy
    {
    public:
        TieredPricing& add_discount(std::string customer_type, int percent)
        {
            discounts_[std::move(customer_type)] = percent;
            return *this;
        }

        std::optional<long long> total_for(const Order& order) const override
        {
            auto it = discounts_.find(order.customer_type);
            if (it == discounts_.end())
                return std::nullopt;
            return static_cast<long long>(order.quantity) * order.unit_price_cents * (100 - it->second) / 100;
        }

    private:
        std::map<std::string, int> discounts_;
    };

    class OrderProcessor
    {
    public:
        OrderProcessor(InventoryService& inventory, PaymentGateway& payments, NotificationService& notifier,
            Logger& logger, const PricingPolicy& pricing)
            : inventory_(inventory)
            , payments_(payments)
            , notifier_(notifier)
            , logger_(logger)
            , pricing_(pricing)
        {
        }

        OrderStatus process(const Order& order)
        {
            logger_.log("processing order for " + order.customer_email);
            if (order.quantity <= 0 || order.unit_price_cents < 0 || order.customer_email.empty())
                return OrderStatus::InvalidOrder;

            const auto total = pricing_.total_for(order);
            if (!total)
                return OrderStatus::InvalidOrder;

            if (!inventory_.reserve(order.item, order.quantity))
                return OrderStatus::OutOfStock;

            if (!payments_.charge(order.payment_method, *total))
            {
                inventory_.release(order.item, order.quantity);
                return OrderStatus::PaymentFailed;
            }

            notifier_.order_confirmed(order);
            return OrderStatus::Confirmed;
        }

    private:
        InventoryService& inventory_;
        PaymentGateway& payments_;
        NotificationService& notifier_;
        Logger& logger_;
        const PricingPolicy& pricing_;
    };
} // namespace Step_4
