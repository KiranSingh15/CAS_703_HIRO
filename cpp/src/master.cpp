#include "../include/master.hpp"
#include <opencv2/opencv.hpp>

Master::Master(size_t numThreads, bool force, bool save) : available(numThreads, true), force(force), save(save) {

    // Load all image filenames from the import path into the task queue
    for (const auto& entry : std::filesystem::directory_iterator(IMPORT_PATH)) {
        queue.push(entry.path().filename());
    }

    std::cout << "Processing " << queue.getSize() << " images." << std::endl; 

    // Start the execution timer
    start = std::chrono::high_resolution_clock::now();

    // Launch all worker threads and store them in the workers vector
    for (size_t i = 1; i < numThreads + 1; i++) {
        workers.emplace_back(Worker(this, i, save));
    }
}

Master::~Master() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;  // Tell workers to stop
    }
    cv_master.notify_all();  // Wake up all workers waiting on the condition variable

    // Join all worker threads
    for (auto& thread : workers) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Calculate duration and log results (only if not in --force mode)
    double duration = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
    if (!force) log_queue.logWorker(available.size(), duration);
}

void Master::handleWorkers() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        // Exit loop if no more tasks
        if (queue.empty()) break;

        // Wait until at least one worker becomes available
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
