#ifndef MASTER_HPP
#define MASTER_HPP

#include "taskQueue.hpp"
#include "worker.hpp"
#include "logs.hpp"
#include <iostream>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <filesystem>
#include <chrono>

extern const std::string IMPORT_PATH;
extern const std::string EXPORT_PATH;

class Worker;

class Master {

private:
    std::vector<std::thread> workers;
    std::vector<bool> available;
    std::mutex mtx;
    std::condition_variable cv_master;
    TaskQueue queue;
    Logs log_queue;
    bool stop = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    bool force;
    bool save;

    friend class Worker;

public:
    Master(size_t numThreads, bool force, bool save);
    ~Master();
    void loadImages();
    void displayImages(const std::string& filename);
    void handleWorkers();

};

#endif // !MASTER_HPP
