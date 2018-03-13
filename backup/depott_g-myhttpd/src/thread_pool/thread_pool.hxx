#pragma once

#include "thread_pool.hh"

void work(std::deque<std::function<void()>>* waiting_queue,
          std::mutex* mut, bool* stop)
{
    while (!(*stop) || !waiting_queue->empty())
    {
        std::function<void()> cur_func;
        {
            std::unique_lock<std::mutex> lock(*mut);
            // std::cout << "Went through lock " << i << std::endl;
            while (!(*stop) && waiting_queue->empty())
            {
            }

            if (*stop && waiting_queue->empty())
                return;

            cur_func = waiting_queue->front();
            waiting_queue->pop_front();
        }

        /*mut->unlock();*/

        // std::cout << "Function execution " << i << std::endl;
        if (cur_func)
            cur_func();
        // else
            // std::cout << "Invalid" << std::endl;
    }
}

ThreadPool::ThreadPool(size_t nb_threads)
    : stop_(false)
{
    for (size_t i = 0; i < nb_threads; i++)
    {
        // std::cout << "Creating thread " << i << std::endl;
        threads_.push_back(std::thread(work, &waiting_queue_, &mut_, &stop_, i));
    }
}

ThreadPool::~ThreadPool()
{
    stop_ = true;
    // std::cout << "Stopped threadpool" << std::endl;
    for (auto it = threads_.begin(); it != threads_.end(); ++it)
    {
        // std::cout << "Joining thread" << std::endl;
        (*it).join();
    }
}

void ThreadPool::add_func(std::function<void()> f)
{
    waiting_queue_.push_front(f);
}

void ThreadPool::add_waiting_server(Server* s)
{
    waiting_servers_threads_.push_back(std::thread(&Server::wait, s));
    // std::cout << "Added thread "
    //           << waiting_servers_threads_.back().get_id() << std::endl;
}
