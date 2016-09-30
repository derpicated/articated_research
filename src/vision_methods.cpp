#include "vision_methods.hpp"

vision_methods::vision_methods () {
}

vision_methods::~vision_methods () {
}

cv::Mat vision_methods::preprocessing (const cv::Mat image_in) {
    cv::Mat image_out;
    cvtColor (image_in, image_out, CV_BGR2GRAY);
    cv::GaussianBlur (image_out, image_out, cv::Size (_ksize_x, _ksize_y), _sigma_x, _sigma_y);
    return image_out;
}
