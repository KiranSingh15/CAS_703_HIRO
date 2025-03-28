#ifndef WORKER_HPP
#define WORKER_HPP

#include <chrono>
#include <string>
#include <opencv2/opencv.hpp>
#include "imageOperations.hpp"
#include "master.hpp"

class Master;

class Worker {

private:
    // Attributes
    Master* master;
    size_t pid;
    std::string filename;

public:
    // Constructor
    Worker(Master* master, size_t pid) : master(master), pid(pid) {};

    void operator()();

    // Methods
    void processingImages();

};

#endif // !WORKER_HPP
