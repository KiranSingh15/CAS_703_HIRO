#include "../include/master.hpp"
#include <chrono>
#include <opencv2/opencv.hpp>

Master::Master(size_t numThreads, bool force) : available(numThreads, true), force(force) {

    for (const auto& entry : std::filesystem::directory_iterator(IMPORT_PATH)) {
        queue.push(entry.path().filename());
    }

    std::cout << "Processing " << queue.getSize() << " images." << std::endl; 

    start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < numThreads + 1; i++) {
        workers.emplace_back(Worker(this, i));
    }
}

Master::~Master() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv_master.notify_all();

    for (auto& thread : workers) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    double duration = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();

    if (!force) log_queue.logWorker(available.size(), duration);
}

void Master::handleWorkers() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        if (queue.empty()) break;
        cv_master.wait(lock, [this] { 
            return std::find(available.begin(), available.end(), true) != available.end();
        });

        // Find an available thread 
        for (size_t i = 0; i < workers.size(); ++i) {
            if (available[i]) {
                cv_master.notify_one();
                break;
            }
        }
    }    
}

// void Master::displayImages(const std::string& filename) {
//     // Display results
//     cv::imshow("RGB Image", IMPORT_PATH + filename);
//     // cv::imshow("Grayscale Image", grayscaleImage);
//     // cv::imshow("Smoothed Image", smoothedImage);
//     cv::imshow("2nd Order Laplacian", EXPORT_PATH + filename);
//     cv::waitKey(0);
//     cv::destroyAllWindows();
// }

