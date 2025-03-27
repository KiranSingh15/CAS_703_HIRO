#include "../include/taskQueue.hpp"


bool TaskQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.empty();
}
