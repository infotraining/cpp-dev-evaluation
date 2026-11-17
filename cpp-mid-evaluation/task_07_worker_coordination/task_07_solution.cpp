#include "task_07_solution.hpp"

#include <memory>

namespace Solution
{
WorkerGroup::WorkerGroup(std::size_t worker_count, Work work)
    : worker_count_(worker_count), work_(std::move(work))
{
    if (worker_count_ == 0)
    {
        throw std::invalid_argument("worker count must be positive");
    }
    if (!work_)
    {
        throw std::invalid_argument("work callback must not be empty");
    }
}

WorkerGroup::~WorkerGroup()
{
    request_stop();
    join();
}

void WorkerGroup::start()
{
    std::lock_guard lock(lifecycle_mutex_);
    if (started_)
    {
        throw std::logic_error("workers have already been started");
    }
    started_ = true;
    auto startup_gate = std::make_shared<std::latch>(static_cast<std::ptrdiff_t>(worker_count_));
    workers_.reserve(worker_count_);
    std::size_t launched = 0;
    try
    {
        for (std::size_t index = 0; index < worker_count_; ++index)
        {
            workers_.emplace_back([this, startup_gate](std::stop_token token) {
                startup_gate->count_down();
                startup_gate->wait();
                work_(token);
            });
            ++launched;
        }
    }
    catch (...)
    {
        for (std::size_t index = launched; index < worker_count_; ++index)
        {
            startup_gate->count_down();
        }
        for (auto& worker : workers_)
        {
            worker.request_stop();
        }
        startup_gate->wait();
        for (auto& worker : workers_)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
        throw;
    }
    startup_gate->wait();
}

void WorkerGroup::request_stop()
{
    std::lock_guard lock(lifecycle_mutex_);
    for (auto& worker : workers_)
    {
        worker.request_stop();
    }
}

void WorkerGroup::join()
{
    std::lock_guard lock(lifecycle_mutex_);
    for (auto& worker : workers_)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}
}
