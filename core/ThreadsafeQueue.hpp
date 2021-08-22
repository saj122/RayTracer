#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadsafeQueue
{
    public:
        ThreadsafeQueue() {}
        ThreadsafeQueue(ThreadsafeQueue const& other)
        {
            std::scoped_lock<std::mutex> lk(other._mut);
            _data_queue = other._data_queue;
        }

        void push(T new_value)
        {
            std::scoped_lock<std::mutex> lk(_mut);
            _data_queue.push(new_value);
            _data_cond.notify_one();    
        }

        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(_mut);
            _data_cond.wait(lk,[this]{return !_data_queue.empty();});
            value = _data_queue.front();
            _data_queue.pop();
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(_mut);
            _data_cond.wait(lk,[this]{return !_data_queue.empty();});
            std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
            _data_queue.pop();
            return res;
        }

        bool try_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(_mut);
            if(_data_queue.empty())
                return false;
            value = _data_queue.front();
            _data_queue.pop();
            return true;
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(_mut);
            if(_data_queue.empty())
                return std::shared_ptr<T>();
            std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
            _data_queue.pop();
            return res;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(_mut);
            return _data_queue.empty();
        }
    private:
        mutable std::mutex _mut;
        std::queue<T> _data_queue;
        std::condition_variable _data_cond;
};

#endif