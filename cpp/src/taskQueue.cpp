#include "../include/taskQueue.hpp"
#include <mutex>

void TaskQueue::push(const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(value);
    // cond_var.notify_one();
}

bool TaskQueue::pop(std::string& value) {
    std::lock_guard<std::mutex> lock(mutex);
    // cond_var.wait(lock, [this] {return !queue.empty();});

    if (queue.empty()) return false;
    value = queue.front();
    queue.pop();
    return true;
}

bool TaskQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.empty();
}

const size_t TaskQueue::getSize() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.size();
}
