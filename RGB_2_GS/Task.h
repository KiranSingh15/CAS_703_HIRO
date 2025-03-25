#ifndef TASK_H
#define TASK_H

#include <opencv2/opencv.hpp>
#include <functional>

struct Metrics {
    double execution_time_ms;   // Execution time in milliseconds
    size_t memory_usage_bytes;  // Memory usage in bytes

    Metrics();
    Metrics(double time, size_t memory);
};

class Task {
public:
    using TaskCallback = std::function<void(int, cv::Mat, Metrics)>;

private:
    int id;
    cv::Mat image;
    TaskCallback callback;

public:
    Task(int task_id, const cv::Mat& img, TaskCallback cb);

    int getId() const;
    const cv::Mat& getImage() const;
    void complete(const cv::Mat& result, const Metrics& metrics) const;
};

#endif // TASK_H
