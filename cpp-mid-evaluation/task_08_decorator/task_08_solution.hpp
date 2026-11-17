#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Solution
{
    class MessageSink
    {
    public:
        virtual ~MessageSink() = default;
        virtual void send(const std::string& message) = 0;
    };

    class RecordingSink : public MessageSink
    {
    public:
        void send(const std::string& message) override;
        const std::vector<std::string>& messages() const;

    private:
        std::vector<std::string> messages_;
    };

    class ValidatingSink : public MessageSink
    {
    public:
        explicit ValidatingSink(std::unique_ptr<MessageSink> next);
        void send(const std::string& message) override;

    private:
        std::unique_ptr<MessageSink> next_;
    };

    class AuditSink : public MessageSink
    {
    public:
        explicit AuditSink(std::unique_ptr<MessageSink> next);
        void send(const std::string& message) override;
        const std::vector<std::string>& audit_log() const;

    private:
        std::unique_ptr<MessageSink> next_;
        std::vector<std::string> audit_log_;
    };
} // namespace Solution
