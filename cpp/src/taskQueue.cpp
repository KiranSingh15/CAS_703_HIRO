#include "../include/taskQueue.hpp"
#include <mutex>

/**
 * @brief Adds a new task to the queue.
 * 
 * @param value The task (typically a filename) to be added to the queue.
 */
void TaskQueue::push(const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(value);
}

/**
 * @brief Attempts to remove the front task from the queue.
 * 
 * @param value Output parameter where the task will be stored if successful.
 * @return true if a task was successfully removed.
 * @return false if the queue was empty.
 */
bool TaskQueue::pop(std::string& value) {
    std::lock_guard<std::mutex> lock(mutex);

    if (queue.empty()) return false;

    value = queue.front();
    queue.pop();
    return true;
}

/**
 * @brief Checks whether the queue is empty.
 * 
 * @return true if the queue is empty.
 * @return false if the queue contains at least one element.
 */
bool TaskQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.empty();
}

/**
 * @brief Gets the number of elements currently in the queue.
 * 
 * @return The size of the queue.
 */
const size_t TaskQueue::getSize() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.size();
}
