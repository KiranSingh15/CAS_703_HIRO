#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include "../include/master.hpp"

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"

extern const std::string IMPORT_PATH = "../images/";
extern const std::string EXPORT_PATH = "../output/";

int main (int argc, char *argv[]) {
    
    int numThreads = std::thread::hardware_concurrency();

    if (argc == 2) {
        try {
            std::string answer;
            int inputThreads = std::stoi(argv[1]);
            std::cout << "You've asked for " << inputThreads << " threads to run this program.\n";

            if (inputThreads < numThreads) {
                std::cout << "Your computer can support " << GREEN << numThreads << RESET
                          << " threads, are you sure you want to run with only " << YELLOW << inputThreads << RESET << " threads? [y/n]: ";
                std::cin >> answer;
                if (answer == "y" || answer == "Y") {
                    numThreads = inputThreads;
                }
            } else if (inputThreads > numThreads) {
                std::cout << RED << "Warning: " << RESET << "Your computer can only support " << GREEN << numThreads << RESET 
                          << " threads efficiently. Do you still want to use " << YELLOW << inputThreads << RESET << " threads? [y/n]: ";
                std::cin >> answer;
                if (answer == "y" || answer == "Y") {
                    numThreads = inputThreads;
                }
            } else {
                numThreads = inputThreads;
            }
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Not a number\n";
            return 1;
        } catch (const std::out_of_range&) {
            std::cerr << "Number out of range\n";
            return 1;
        }
    }

    std::cout << "Running with " << BLUE << numThreads << RESET << " threads.\n";

    // Continue with master-slave execution
    // Master master(numThreads);
    // master.loadImages();
    //
    //
    // // Load an image
    // cv::Mat rgbImage = cv::imread(files[0], cv::IMREAD_COLOR);
    // if (rgbImage.empty()) {
    //     std::cerr << "Error: Could not open or find the image!" << std::endl;
    //     return -1;
    // }
    //
    // Worker slave(files[0]);
    // slave.loggingMetrics();
    //
    // // Download the images
    // cv::imwrite(EXPORT_PATH + "cybertruck.jpg", laplacianImage);

    std::cout << "Done !\n";

    return 0;
}
