#include "slave.h"
#include <iostream>

Slave::Slave(int id) : id(id) {}

cv::Mat Slave::processImage(const cv::Mat& img) {
    // Start timing the image processing
    auto start = std::chrono::high_resolution_clock::now();

    // Step 1: Convert image to grayscale
    cv::Mat gray = convertToGrayscale(img);

    // Step 2: Apply Gaussian smoothing filter
    cv::Mat smoothed = applyGaussianFilter(gray, 5, 1.5);

    // Step 3: Apply Laplacian filter
    cv::Mat result = applyLaplacianFilter(smoothed, 3, 1.0, 0.0);

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Log the processing time
    std::cout << "Slave " << id << " processed image in " << elapsed.count() << " seconds\n";

    return result;
}
