#include "../include/logs.hpp"
#include <cstddef>
#include <fstream>
#include <ios>
#include <string>

void Logs::logWorker(size_t num_threads, double total_duration) {
    std::ofstream log_file(EXPORT_PATH + "metrics-" + std::to_string(num_threads) + "threads.log", std::ios::trunc);

    std::unordered_map<int, int> thread_work_count;  // Number of images processed by each thread
    std::unordered_map<int, size_t> thread_size_count; // file size processed by each thread
    size_t total_images = 0;
    size_t total_size = 0;
    double total_time = 0.0; 

    while (true) {
        std::unique_lock<std::mutex> lock(log_mutex);
        if (log_queue.empty()) break;

        std::string log_entry = log_queue.front();
        log_queue.pop();
        log_file << log_entry;

        // Extract thread ID and filename
        std::istringstream iss(log_entry);
        std::string word, filename, time;
        int thread_id = -1;
        while (iss >> word) {
            if (word == "Thread") {
                iss >> thread_id;
            } else if (word == "processed") {
                iss >> filename;
            } else if (word == "in") {
                iss >> time;
            }
        }

        // Check for successful extraction
        if (thread_id != -1 && !filename.empty() && !time.empty()) {
            thread_work_count[thread_id]++;
            total_images++;

            // Get file size
            size_t file_size = 0;
            if (!filename.empty()) {
                std::string filepath = IMPORT_PATH + filename;
                if (std::filesystem::exists(filepath)) {
                    file_size = std::filesystem::file_size(filepath);
                }
            }
            thread_size_count[thread_id] += file_size;
            total_size += file_size;

            try {
                total_time += std::stod(time); 
            } catch (const std::exception& e) {
                std::cerr << "Error converting time: " << time << " - " << e.what() << std::endl;
            }
        }
    }

    // Add final metrics
    log_file << "\n==== Execution Summary ====\n";
    log_file << "Total execution time: " << total_duration << " ms\n";
    log_file << "Total thread execution time: " << total_time << " ms\n";
    log_file << "Total images processed: " << total_images << "\n";
    log_file << "Total size processed: " << total_size / (1024.0 * 1024.0) << " MB\n";
    log_file << "Work distribution:\n";

    for (const auto& [thread_id, count] : thread_work_count) {
        double percentage = (count / static_cast<double>(total_images)) * 100.0;
        double size_mb = thread_size_count[thread_id] / (1024.0 * 1024.0);
        log_file << "Thread " << thread_id << ": " << count << " images (" << percentage << "%), "
                 << size_mb << " MB processed\n";
    }

    log_file.close();

    std::cout << "\n\n============== \033[1;4mExecution Summary\033[0m ==============\n\n";
    std::cout << std::setw(30) << "Total execution time: " << std::setw(10) << total_duration << " ms\n";
    std::cout << std::setw(30) << "Total thread execution time: " << std::setw(10) << total_time << " ms\n";
    std::cout << std::setw(30) << "Total images processed: " << std::setw(10) << total_images << "\n";
    std::cout << std::setw(30) << "Total size processed: " << std::setw(10) << std::fixed << std::setprecision(2) << total_size / (1024.0 * 1024.0) << " MB\n";
    
    // Highlight estimated gains
    std::cout << std::setw(30) << "Estimated gains: " << "\033[1;92m" << std::setw(10) << std::fixed << std::setprecision(2) << (total_time/total_duration)*100 << "%\033[0m\n";

}

void Logs::logThreadExecution(int thread_id, const std::string& filename, double duration) {
    size_t file_size = 0;
    std::string filepath = IMPORT_PATH + filename;
    
    if (std::filesystem::exists(filepath)) {
        file_size = std::filesystem::file_size(filepath) / (1024.0 * 1024.0);
    }

    std::lock_guard<std::mutex> lock(log_mutex);
    log_queue.push("Thread " + std::to_string(thread_id) + 
                   " processed " + filename + 
                   " (" + std::to_string(file_size) + " MB) in " + 
                   std::to_string(duration) + " ms\n");
}
