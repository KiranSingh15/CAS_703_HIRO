#include "Slave.h"
#include "timer.h"

class slaveModule {
private:
    bool slaveBusy;
    int slaveID, gaussKernSize, lpKernSize;
    double sigma, scale, delta;
    cv::Mat inputImage, greyscaleImage, smoothedImage, laplacianImage, absLaplacian;
    Timer clock();


public:
    void setInputValues(int gks, int lpks, double sd, double sc, double dlt);
    void setInputImage(const cv::Mat& image);
    void convertToGrayscale();
    void applyGaussianFilter();
    void applyLaplacianFilter();
    cv::Mat getProcessedImage() const;
    void showImages() const;
    void engageSlave();
    void disengageSlave();
    bool getSlaveStatus();
    void resetTimer();
    void checkElapsedTime();
};

void slaveModule::setInputValues(int gks, int lpks, double sd, double sc, double dlt) {
    gaussKernSize = gks;
    lpKernSize = lpks;
    sigma = sd;
    scale = sc;
    delta = dlt;
}

void slaveModule::setInputImage(const cv::Mat& image) {
    if (image.empty()) {
        throw std::runtime_error("Input image is empty.");
    }
    inputImage = image;
}

void slaveModule::convertToGrayscale() {
    cv::cvtColor(inputImage, greyscaleImage, cv::COLOR_BGR2GRAY);
}

void slaveModule::applyGaussianFilter() {
    cv::GaussianBlur(greyscaleImage, smoothedImage, cv::Size(gaussKernSize, gaussKernSize), sigma);
}

void slaveModule::applyLaplacianFilter() {
    cv::Laplacian(smoothedImage, laplacianImage, CV_64F, lpKernSize, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(laplacianImage, absLaplacian);
}

cv::Mat slaveModule::getProcessedImage() const {
    return absLaplacian;
}

void slaveModule::showImages() const {
    cv::imshow("Original Image", inputImage);
    cv::imshow("Grayscale Image", greyscaleImage);
    cv::imshow("Smoothed Image", smoothedImage);
    cv::imshow("Laplacian Filtered Image", absLaplacian);
    cv::waitKey(0);
}

void engageSlave(){
	slaveBusy = true;
}

void disengageSlave(){
	slaveBusy = false;
}

bool getSlaveStatus(){
	return slaveBusy;
}

void resetTimer(){
    clock.reset();
}

void checkElapsedTime(){
    clock.elapsed();
}


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl;
        return 1;
    }

    try {
        slaveModule processor;
        processor.setInputValues(5, 3, 1.0, 1.0, 0.0);

        cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
        processor.setInputImage(image);
        processor.convertToGrayscale();
        processor.applyGaussianFilter();
        processor.applyLaplacianFilter();

        processor.showImages();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
