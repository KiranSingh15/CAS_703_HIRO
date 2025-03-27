#include "../include/worker.hpp"
#include <iostream>
#include <mutex>


// void Worker::loggingMetrics() {
//     start = std::chrono::high_resolution_clock::now();
//
//     for (volatile int i = 0; i<10000; i++);
//
//     duration = start - std::chrono::high_resolution_clock::now();
//
//     std::cout << duration.count() << std::endl;
// }

void Worker::operator()() {
    while (true) {
        std::unique_lock<std::mutex> lock(master->mtx);
        master->cv_master.wait(lock, [this] {return master->stop || !master->queue.empty(); });

        if  (master->stop) return;

        master->queue.pop(filename);
    }
}

void Worker::processingImages() {
    cv::Mat rgbImage = cv::imread(filename, cv::IMREAD_COLOR);
    if (rgbImage.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        // return -1;
    }
    // Convert to grayscale
    cv::Mat grayscaleImage = convertToGrayscale(rgbImage);

    // Apply Gaussian filter
    cv::Mat smoothedImage = applyGaussianFilter(grayscaleImage, 5, 1.5);    // kernel size and std deviation

    // Apply Laplacian filter after Gaussian smoothing
    cv::Mat laplacianImage = applyLaplacianFilter(smoothedImage, 3 , 1, 0);    // kernel_size, scale, and delta/offset
}
