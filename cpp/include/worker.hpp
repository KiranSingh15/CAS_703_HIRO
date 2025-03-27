#ifndef WORKER_HPP
#define WORKER_HPP

#include <chrono>
#include <string>
#include "imageOperations.hpp"
#include "master.hpp"

class Master;

class Worker {

private:
    // Attributes
    Master* master;
    size_t pid;
    // std::chrono::high_resolution_clock::time_point start;
    // std::chrono::duration<double> duration;
    std::string filename;

public:
    // Constructor
    Worker(Master* master, size_t pid) : master(master), pid(pid) {};

    void operator()();

    // Methods
    void loggingMetrics();
    void processingImages();

};

#endif // !WORKER_HPP
