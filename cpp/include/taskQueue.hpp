#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class TaskQueue {

private: 
    std::queue<std::string> queue;
    std::mutex mutex;
    std::condition_variable cond_var;

public:
    void push(const std::string& value);
    bool pop(std::string& value);
    bool empty();
    const size_t getSize() const { return queue.size(); }
};

#endif // IMAGE_OPERATIONS_HPP

