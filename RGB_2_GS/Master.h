#ifndef MASTER_H
#define MASTER_H

#include "task_queue.h"
#include "slave.h"
#include <vector>
#include <thread>

class Master {
public:
    explicit Master(int numSlaves);
    ~Master();
    void addTask(const cv::Mat& img);

private:
    void workerThread(Slave& slave);
    TaskQueue<cv::Mat> taskQueue;
    std::vector<std::thread> workers;
    std::vector<Slave> slaves;
    std::mutex outputMutex;
};

#endif // MASTER_H
