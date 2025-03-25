#include "Master.h"
#include <iostream>

Master::Master(int num_slaves) : running(true) {
    for (int i = 0; i < num_slaves; ++i) {
        slaves.push_back(std::make_unique<Slave>(i));
    }
    worker = std::thread(&Master::workerThread, this);
}

Master::~Master() {
    running = false;
    queue_cv.notify_all();
    if (worker.joinable()) {
        worker.join();
    }
}

void Master::assignTask(const cv::Mat& image) {
    static int task_id_counter = 0;
    int task_id = task_id_counter++;

    auto callback = [this](int id, cv::Mat result, Metrics metrics) {
        std::cout << "Task " << id << " completed in " 
                  << metrics.execution_time_ms << " ms, Memory: "
                  << metrics.memory_usage_bytes << " bytes.\n";
    };

    std::lock_guard<std::mutex> lock(queue_mutex);
    task_queue.emplace(task_id, image, callback);
    queue_cv.notify_one();
}

void Master::workerThread() {
    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [this] { return !task_queue.empty() || !running; });

        if (!running) break;

        Task task = std::move(task_queue.front());
        task_queue.pop();
        lock.unlock();

        static int next_slave = 0;
        slaves[next_slave % slaves.size()]->processTask(task);
        next_slave++;
    }
}