#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class TaskQueue {
public:
    void push(T task);
    bool pop(T& task);
    bool empty();

private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cv;
};

#include "task_queue.cpp"  // Include implementation for templates
#endif // TASK_QUEUE_H