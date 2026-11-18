#pragma once

#include <cstddef>
#include <functional>
#include <stop_token>
#include <utility>
#include <vector>

class WorkerGroup
{
public:
    using Work = std::function<void(std::stop_token)>;

    WorkerGroup(std::size_t worker_count, Work work);
    ~WorkerGroup();
    void start();
    void request_stop();
    void join();

private:
    std::size_t worker_count_;
    Work work_;
};
