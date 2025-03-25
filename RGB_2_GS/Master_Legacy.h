#ifndef MASTER_H
#define MASTER_H


#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>
#include <vector>

#include "Slave.h"
#include "Task.h"

class Slave;

class Master {
private:
    std::vector<std::unique_ptr<Slave>> slaves;
    std::queue<Task> task_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    std::atomic<bool> running;
    std::thread worker;

    void workerThread(); // Function declaration only

public:
    explicit Master(int num_slaves);
    ~Master();

    void assignTask(const cv::Mat& image);
    void start();
};

#endif // MASTER_H
