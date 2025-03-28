#include "../include/master.hpp"
#include <opencv2/opencv.hpp>

Master::Master(size_t numThreads) : available(numThreads, true) {

    for (const auto& entry : std::filesystem::directory_iterator(IMPORT_PATH)) {
        queue.push(entry.path().filename());
    }

    std::cout << "Processing " << queue.getSize() << " images." << std::endl; 

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

    log_queue.logWorker(available.size());
}

void Master::handleWorkers() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        if (queue.getSize() == 0) break;
        cv_master.wait(lock, [this] { 
            return std::find(available.begin(), available.end(), true) != available.end();
        });

        // Trouver un thread disponible
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

