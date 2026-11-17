#include "task_08.hpp"

#include <utility>

void RecordingSink::send(const std::string& message)
{
    (void)message;
}

const std::vector<std::string>& RecordingSink::messages() const
{
    return messages_;
}

ValidatingSink::ValidatingSink(std::unique_ptr<MessageSink> next)
    : next_(std::move(next))
{
}

void ValidatingSink::send(const std::string& message)
{
    (void)message;
}

AuditSink::AuditSink(std::unique_ptr<MessageSink> next)
    : next_(std::move(next))
{
}

void AuditSink::send(const std::string& message)
{
    (void)message;
}

const std::vector<std::string>& AuditSink::audit_log() const
{
    return audit_log_;
}
