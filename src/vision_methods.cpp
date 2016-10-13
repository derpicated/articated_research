#include "vision_methods.hpp"
#include <opencv2/opencv.hpp>

vision_methods::vision_methods () {
}

vision_methods::~vision_methods () {
}

cv::Mat vision_methods::preprocessing (const cv::Mat& image_in) {
    cv::Mat image_out;
    cvtColor (image_in, image_out, CV_BGR2GRAY);
    cv::GaussianBlur (image_out, image_out, cv::Size (_ksize_x, _ksize_y), _sigma_x, _sigma_y);
    return image_out;
}

cv::Mat vision_methods::segmentation (const cv::Mat& image_in) {
    return image_in;
}

std::map<unsigned int, cv::KeyPoint> vision_methods::set_reference (cv::Mat& image_reference) {
    (void)image_reference;
    return {};
}

std::map<unsigned int, cv::KeyPoint> vision_methods::set_reference_keypoints (
const std::map<unsigned int, cv::KeyPoint>& keypoints) {
    (void)keypoints;
    return {};
}

void classification (const std::map<unsigned int, cv::KeyPoint>& markers) {
    (void)markers;
}
