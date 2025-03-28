#include "../include/worker.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <mutex>

void Worker::operator()() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(master->mtx);
            master->cv_master.wait(lock, [this] {return master->stop || !master->queue.empty(); });

            if  (master->stop) return;

            master->queue.pop(filename);
            master->available[pid] = false;
        }

        processingImages();

        {
            std::unique_lock<std::mutex> lock(master->mtx);
            master->available[pid] = true;
        }
        master->cv_master.notify_one();
    }
}

void Worker::processingImages() {

    start = std::chrono::high_resolution_clock::now();

    cv::Mat rgbImage = cv::imread(IMPORT_PATH + filename, cv::IMREAD_COLOR);
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

    duration = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Thread " << pid << " processed " << filename << " which took : " << duration.count() << "seconds." << std::endl;

   cv::imwrite(EXPORT_PATH + filename, laplacianImage); 

}
