#include "master.h"
#include <opencv2/opencv.hpp>

int main() {
    Master master(5);

    cv::Mat image = cv::imread("image.jpg");
    if (image.empty()) {
        std::cerr << "Error: Could not load image\n";
        return 1;
    }

    int rows = image.rows / 2;
    int cols = image.cols / 2;

    cv::Mat subImage1 = image(cv::Rect(0, 0, cols, rows));
    cv::Mat subImage2 = image(cv::Rect(cols, 0, cols, rows));
    cv::Mat subImage3 = image(cv::Rect(0, rows, cols, rows));
    cv::Mat subImage4 = image(cv::Rect(cols, rows, cols, rows));

    master.addTask(subImage1);
    master.addTask(subImage2);
    master.addTask(subImage3);
    master.addTask(subImage4);

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Allow processing time

    return 0;
}
