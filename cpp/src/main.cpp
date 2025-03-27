#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <filesystem>
#include <vector>
#include <thread>
#include "../include/imageOperations.hpp"
#include "../include/worker.hpp"

int main (int argc, char *argv[]) {

    const std::string IMPORT_PATH = "../images/";
    const std::string EXPORT_PATH = "../output/";

    // int numThreads = std::thread::hardware_concurrency();
    // std::cout << numThreads << std::endl;

    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(IMPORT_PATH))
        files.push_back(entry.path());

    // Load an image
    cv::Mat rgbImage = cv::imread(files[0], cv::IMREAD_COLOR);

    if (rgbImage.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Convert to grayscale
    cv::Mat grayscaleImage = convertToGrayscale(rgbImage);

    // Apply Gaussian filter
    cv::Mat smoothedImage = applyGaussianFilter(grayscaleImage, 5, 1.5);    // kernel size and std deviation

    // Apply Laplacian filter after Gaussian smoothing
    cv::Mat laplacianImage = applyLaplacianFilter(smoothedImage, 3 , 1, 0);    // kernel_size, scale, and delta/offset

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Compute the duration
    std::chrono::duration<double> duration = end - start;
    
    // Print the elapsed time
    std::cout << "Processing Time: " << duration.count() << " seconds" << std::endl;


    // Display results
    // cv::imshow("RGB Image", rgbImage);
    // cv::imshow("Grayscale Image", grayscaleImage);
    // cv::imshow("Smoothed Image", smoothedImage);
    // cv::imshow("2nd Order Laplacian", laplacianImage);
    // cv::waitKey(0);
    // cv::destroyAllWindows();
    
    Worker slave(files[0]);
    slave.loggingMetrics();

    // Download the images
    cv::imwrite(EXPORT_PATH + "cybertruck.jpg", laplacianImage);

    std::cout << "Done !\n";

    return 0;
}
