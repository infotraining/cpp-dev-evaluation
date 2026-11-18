#include "task_08_solution.hpp"

#include <utility>

namespace Solution
{
    void RecordingSink::send(const std::string& message)
    {
        messages_.push_back(message);
    }

    const std::vector<std::string>& RecordingSink::messages() const
    {
        return messages_;
    }

    ValidatingSink::ValidatingSink(std::unique_ptr<MessageSink> next)
        : next_(std::move(next))
    {
        if (!next_)
        {
            throw std::invalid_argument("decorator requires a wrapped sink");
        }
    }

    void ValidatingSink::send(const std::string& message)
    {
        if (message.empty())
        {
            throw std::invalid_argument("message must not be empty");
        }
        next_->send(message);
    }

    AuditSink::AuditSink(std::unique_ptr<MessageSink> next)
        : next_(std::move(next))
    {
        if (!next_)
        {
            throw std::invalid_argument("decorator requires a wrapped sink");
        }
    }

    void AuditSink::send(const std::string& message)
    {
        audit_log_.push_back(message);
        next_->send(message);
    }

    const std::vector<std::string>& AuditSink::audit_log() const
    {
        return audit_log_;
    }
} // namespace Solution
