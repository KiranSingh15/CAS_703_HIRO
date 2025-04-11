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
    bool save;

public:
    // Constructor
    Worker(Master* master, size_t pid, bool save) : master(master), pid(pid), save(save) {};

    void operator()();

    // Methods
    void processingImages();

};

#endif // !WORKER_HPP
