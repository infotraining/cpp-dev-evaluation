#include "task_07.hpp"

WorkerGroup::WorkerGroup(std::size_t worker_count, Work work)
    : worker_count_(worker_count), work_(std::move(work))
{
}

WorkerGroup::~WorkerGroup() = default;

void WorkerGroup::start()
{
}

void WorkerGroup::request_stop()
{
}

void WorkerGroup::join()
{
}
