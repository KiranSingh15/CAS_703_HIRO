#ifndef WORKER_HPP
#define WORKER_HPP

#include <chrono>
#include <string>

class Worker {

private:
    // Attributes
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::duration<double> duration;
    std::string filename;

public:
    // Constructor
    explicit Worker(const std::string& name) : duration(0.0), filename(name) {}

    // Methods
    void loggingMetrics();
    void processingImages();

};

#endif // !WORKER_HPP
