#ifndef SLAVE_H
#define SLAVE_H

#include <chrono>
#include "imageOperations.h"
#include <opencv2/opencv.hpp>


class Slave {
    public:
        explicit Slave(int id);
        cv::Mat processImage(const cv::Mat& img);
    
    private:
        int id;
    };

#endif // SLAVE_H
