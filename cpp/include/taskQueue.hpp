#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <cstddef>
#include <queue>
#include <mutex>
#include <string>

class TaskQueue {

private: 
    std::queue<std::string> queue;
    std::mutex mutex;

public:
    void push(const std::string& value);
    bool pop(std::string& value);
    bool empty();
    const size_t getSize();
};

#endif
