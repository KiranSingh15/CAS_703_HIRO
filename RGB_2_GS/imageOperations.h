#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#include <opencv2/opencv.hpp>


cv::Mat convertToGrayscale(const cv::Mat& inputImage);
cv::Mat applyGaussianFilter(const cv::Mat& inputImage, int kernelSize, double sigma);
cv::Mat applyLaplacianFilter(const cv::Mat& inputImage, int kernelSize = 3, double scale = 1.0, double delta = 0.0);


#endif //IMAGE_OPERATIONS_H