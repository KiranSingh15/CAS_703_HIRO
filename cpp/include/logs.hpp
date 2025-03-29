#ifndef LOGS_HPP
#define LOGS_HPP

#include <cstddef>
#include <queue>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <filesystem>

extern const std::string EXPORT_PATH;
extern const std::string IMPORT_PATH;

class Logs {
private:
    std::queue<std::string> log_queue;
    std::mutex log_mutex;

public:
    void logWorker(size_t num_threads, double total_duration);
    void logThreadExecution(int thread_id, const std::string& filename, double duration);
};

#endif 
