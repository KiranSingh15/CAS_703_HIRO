#include "Task.h"

Metrics::Metrics() : execution_time_ms(0), memory_usage_bytes(0) {}

Metrics::Metrics(double time, size_t memory) 
    : execution_time_ms(time), memory_usage_bytes(memory) {}

Task::Task(int task_id, const cv::Mat& img, TaskCallback cb)
    : id(task_id), image(img), callback(std::move(cb)) {}

int Task::getId() const {
    return id;
}

const cv::Mat& Task::getImage() const {
    return image;
}

void Task::complete(const cv::Mat& result, const Metrics& metrics) const {
    if (callback) {
        callback(id, result, metrics);
    }
}
