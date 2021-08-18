#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <iostream>
#include <condition_variable>

#include "ThreadsafeQueue.hpp"

class ThreadPool
{
    public:
        ThreadPool() : _done(false)
        {
            unsigned const thread_count = std::thread::hardware_concurrency();
            std::cout << "Number of threads: " << thread_count << std::endl;
            try
            {
                for(unsigned int i = 0;i < thread_count;++i)
                {
                    _threads.push_back(std::thread(&ThreadPool::worker_thread,this));
                }
            }
            catch(const std::exception& e)
            {
                _done = true;
                throw;
            }
            
        }

        ~ThreadPool()
        {
            _done = true;
            for(auto& thread : _threads)
            {
                if(thread.joinable())
                    thread.join();
            }
        }

        void waitFinished()
        {
            std::unique_lock<std::mutex> lock(_mut);
            _cv_finished.wait(lock, [this](){ return _work_queue.empty(); });
        }

        template<typename FunctionType>
        void submit(FunctionType f)
        {
            _work_queue.push(std::function<void()>(f));
        }
    private:
        std::vector<std::thread> _threads;
        std::atomic_bool _done;
        std::condition_variable _cv_finished;
        std::mutex _mut;
        ThreadsafeQueue<std::function<void()>> _work_queue;

    private:
        void worker_thread()
        {
            while(!_done)
            {
                std::function<void()> task;
                if(_work_queue.try_pop(task))
                {
                    task();
                    _cv_finished.notify_one();
                }
                else 
                {
                    std::this_thread::yield();
                }
            }
        }
};

#endif