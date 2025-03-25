#include "imageOperations.h"

cv::Mat convertToGrayscale(const cv::Mat& inputImage) {
    cv::Mat grayscaleImage;
    cv::cvtColor(inputImage, grayscaleImage, cv::COLOR_BGR2GRAY);
    return grayscaleImage;
}

cv::Mat applyGaussianFilter(const cv::Mat& inputImage, int kernelSize, double sigma) {
    cv::Mat smoothedImage;
    cv::GaussianBlur(inputImage, smoothedImage, cv::Size(kernelSize, kernelSize), sigma);
    return smoothedImage;
}

cv::Mat applyLaplacianFilter(const cv::Mat& inputImage, int kernelSize, double scale, double delta) {
    // Output image to hold the result
    cv::Mat laplacianImage;
    
    // Apply the Laplacian filter (Second derivative)
    cv::Laplacian(inputImage, laplacianImage, CV_64F, kernelSize, scale, delta, cv::BORDER_DEFAULT);
    
    // Convert the result to a more viewable format (CV_8U)
    cv::Mat absLaplacian;
    cv::convertScaleAbs(laplacianImage, absLaplacian);
    
    return absLaplacian;
}