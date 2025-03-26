#ifndef IMAGE_OPERATIONS_HPP
#define IMAGE_OPERATIONS_HPP

#include <opencv2/opencv.hpp>

// Function prototypes
cv::Mat convertToGrayscale(const cv::Mat& inputImage);
cv::Mat applyGaussianFilter(const cv::Mat& inputImage, int kernelSize, double sigma);
cv::Mat applyLaplacianFilter(const cv::Mat& inputImage, int kernelSize, double scale, double delta);

#endif // IMAGE_OPERATIONS_HPP

