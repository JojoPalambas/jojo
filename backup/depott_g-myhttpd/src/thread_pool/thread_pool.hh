#pragma once

#include "../server/server.hh"

#include <thread>
#include <mutex>
#include <vector>
#include <deque>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(size_t nb_workers);
    ~ThreadPool();

    void add_func(std::function<void()> f);
    void add_waiting_server(Server* s);
private:
    std::deque<std::function<void()>> waiting_queue_;
    std::vector<std::thread> threads_;
    std::vector<std::thread> waiting_servers_threads_;

    std::mutex mut_;
    bool stop_;
};

#include "thread_pool.hxx"
