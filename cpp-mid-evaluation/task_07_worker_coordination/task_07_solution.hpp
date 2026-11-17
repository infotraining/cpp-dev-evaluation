#pragma once

#include <cstddef>
#include <functional>
#include <latch>
#include <mutex>
#include <stdexcept>
#include <stop_token>
#include <thread>
#include <vector>

namespace Solution
{
    class WorkerGroup
    {
    public:
        using Work = std::function<void(std::stop_token)>;

        WorkerGroup(std::size_t worker_count, Work work);
        ~WorkerGroup();
        WorkerGroup(const WorkerGroup&) = delete;
        WorkerGroup& operator=(const WorkerGroup&) = delete;

        void start();
        void request_stop();
        void join();

    private:
        const std::size_t worker_count_;
        Work work_;
        std::vector<std::jthread> workers_;
        std::mutex lifecycle_mutex_;
        bool started_{false};
    };
} // namespace Solution
