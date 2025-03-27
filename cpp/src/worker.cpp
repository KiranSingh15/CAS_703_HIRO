#include "../include/worker.hpp"
#include <iostream>


void Worker::loggingMetrics() {
    start = std::chrono::high_resolution_clock::now();

    for (volatile int i = 0; i<10000; i++);

    duration = start - std::chrono::high_resolution_clock::now();

    std::cout << duration.count() << std::endl;
}
