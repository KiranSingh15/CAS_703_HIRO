/* 
#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    // Load an RGB image
    cv::Mat rgbImage = cv::imread("cybertruck.jpg");

    // Check if the image was loaded
    if (rgbImage.empty()) {
        std::cerr << "Error: Could not load image!" << std::endl;
        return -1;
    }

    // Convert to grayscale
    cv::Mat grayImage;
    cv::cvtColor(rgbImage, grayImage, cv::COLOR_BGR2GRAY);

    // Display the images
    cv::imshow("RGB Image", rgbImage);
    cv::imshow("Grayscale Image", grayImage);

    // Wait for a key press and close windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
*/

#include <iostream>
#include "imageOperations.h"
#include "opencv2/opencv.hpp"

// #include "conv2GS.h"
// #include "gKernel.h"
// #include "laplacianFilter.h"
#include "Slave.h"


int main() {
    // Load an image
    cv::Mat rgbImage = cv::imread("cybertruck.jpg", cv::IMREAD_COLOR);
    
    if (rgbImage.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Convert to grayscale
    cv::Mat grayscaleImage = convertToGrayscale(rgbImage);

    // Apply Gaussian filter
    cv::Mat smoothedImage = applyGaussianFilter(grayscaleImage, 5, 1.5);    // kernel size and std deviation

    // Apply Laplacian filter after Gaussian smoothing
    cv::Mat laplacianImage  = applyLaplacianFilter(smoothedImage, 3 , 1, 0);    // kernel_size, scale, and delta/offset


    // Display results
    cv::imshow("RGB Image", rgbImage);
    cv::imshow("Grayscale Image", grayscaleImage);
    cv::imshow("Smoothed Image", smoothedImage);
    cv::imshow("2nd Order Laplacian", laplacianImage);
    cv::waitKey(0);

    return 0;
}


