#ifndef MASTER_HPP
#define MASTER_HPP

#include "taskQueue.hpp"
#include "worker.hpp"
#include <iostream>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <filesystem>

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
    bool stop = false;

    friend class Worker;

public:
    explicit Master(size_t numThreads);
    ~Master();
    void loadImages();
    void displayImages(const std::string& filename);
    void handleWorkers();

};

#endif // !MASTER_HPP
