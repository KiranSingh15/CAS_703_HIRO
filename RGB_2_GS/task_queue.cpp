#include "task_queue.h"

template <typename T>
void TaskQueue<T>::push(T task) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(task);
    cv.notify_one();
}

template <typename T>
bool TaskQueue<T>::pop(T& task) {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !queue.empty(); });
    task = queue.front();
    queue.pop();
    return true;
}

template <typename T>
bool TaskQueue<T>::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}