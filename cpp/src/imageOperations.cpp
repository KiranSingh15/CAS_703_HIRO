#include "../include/imageOperations.hpp"

constexpr int MIN_KERNEL_SIZE = 3;  // Minimum allowed kernel size
constexpr int MAX_KERNEL_SIZE = 31; // Maximum allowed kernel size

/**
 * Converts an input image to grayscale.
 *
 * @param inputImage The original colored image.
 * @return Grayscale version of the input image.
 * @throws std::invalid_argument if the input image is empty.
 */
cv::Mat convertToGrayscale(const cv::Mat& inputImage) {
    if (inputImage.empty()) {
        throw std::invalid_argument("Error: Input image is empty!");
    }
    
    cv::Mat grayscaleImage;
    cv::cvtColor(inputImage, grayscaleImage, cv::COLOR_BGR2GRAY); // Convert to grayscale
    return grayscaleImage;
}

/**
 * Applies a Gaussian blur filter to an image.
 *
 * @param inputImage The input image (grayscale or colored).
 * @param kernelSize Size of the kernel (must be a positive odd number).
 * @param sigma Standard deviation for Gaussian blur.
 * @return Blurred image.
 * @throws std::invalid_argument if the input image is empty or kernel size is invalid.
 */
cv::Mat applyGaussianFilter(const cv::Mat& inputImage, int kernelSize, double sigma) {
    if (inputImage.empty()) {
        throw std::invalid_argument("Error: Input image is empty!");
    }
    if (kernelSize < MIN_KERNEL_SIZE || kernelSize > MAX_KERNEL_SIZE || kernelSize % 2 == 0) {
        throw std::invalid_argument("Error: Kernel size must be an odd number between 3 and 31.");
    }
    if (sigma <= 0) {
        sigma = 1.0; // Set default sigma value if not provided correctly
    }

    cv::Mat smoothedImage;
    cv::GaussianBlur(inputImage, smoothedImage, cv::Size(kernelSize, kernelSize), sigma); // Apply Gaussian filter
    return smoothedImage;
}

/**
 * Applies a Laplacian filter to an image to detect edges.
 *
 * @param inputImage The input image (grayscale or smoothed).
 * @param kernelSize Size of the kernel (must be an odd number).
 * @param scale Scaling factor for the filter response.
 * @param delta Optional bias added to the filtered image.
 * @param ddepth Desired depth of the output image (default: CV_16S).
 * @return Image with detected edges.
 * @throws std::invalid_argument if the input image is empty or kernel size is invalid.
 */
cv::Mat applyLaplacianFilter(const cv::Mat& inputImage, int kernelSize, double scale, double delta) {
    if (inputImage.empty()) {
        throw std::invalid_argument("Error: Input image is empty!");
    }
    if (kernelSize < MIN_KERNEL_SIZE || kernelSize > MAX_KERNEL_SIZE || kernelSize % 2 == 0) {
        throw std::invalid_argument("Error: Kernel size must be an odd number between 3 and 31.");
    }

    cv::Mat laplacianImage;
    int ddepth = inputImage.depth() == CV_8U ? CV_8U : CV_64F;

    cv::Laplacian(inputImage, laplacianImage, ddepth, kernelSize, scale, delta, cv::BORDER_DEFAULT); // Apply Laplacian

    // Convert to absolute scale if the depth is higher (e.g., 16-bit or 64-bit)
    if (ddepth == CV_16S || ddepth == CV_64F) {
        cv::Mat absLaplacian;
        cv::convertScaleAbs(laplacianImage, absLaplacian);
        return absLaplacian;
    }

    return laplacianImage;
}

