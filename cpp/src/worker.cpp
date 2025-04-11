#include "../include/worker.hpp"
#include <chrono>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <mutex>

void Worker::operator()() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(master->mtx);

            // Wait until there's work to do or stop signal is received
            master->cv_master.wait(lock, [this] {
                return master->stop || !master->queue.empty();
            });

            // Exit if the master signaled to stop
            if (master->stop) return;

            // Get a task and mark this worker as busy
            master->queue.pop(filename);
            master->available[pid] = false;
        }

        // Process the assigned image
        processingImages();

        {
            std::unique_lock<std::mutex> lock(master->mtx);

            // Mark this worker as available again
            master->available[pid] = true;

            // Notify master that a worker is free
            master->cv_master.notify_one();
        }
    }
}

void Worker::processingImages() {

    // start a chrono
    auto start = std::chrono::high_resolution_clock::now();

    cv::Mat rgbImage = cv::imread(IMPORT_PATH + filename, cv::IMREAD_COLOR);
    if (rgbImage.empty()) {
        std::cerr << "Error: Could not open or find the image " << filename << std::endl;
        // return -1;
    }
    // Convert to grayscale
    cv::Mat grayscaleImage = convertToGrayscale(rgbImage);

    // Apply Gaussian filter
    cv::Mat smoothedImage = applyGaussianFilter(grayscaleImage, 5, 1.5);    // kernel size and std deviation

    // Apply Laplacian filter after Gaussian smoothing
    cv::Mat laplacianImage = applyLaplacianFilter(smoothedImage, 3 , 1, 0);    // kernel_size, scale, and delta/offset

    // End of the chrono
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(end - start).count();

    // Save the image if desired
    if (save) cv::imwrite(EXPORT_PATH + filename, laplacianImage); 

    // Push logs on a queue
    master->log_queue.logThreadExecution(pid, filename, duration);
}
