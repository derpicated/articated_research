#include "vision_methods.hpp"

// to greyscale
// gaussian blur
// edge detect
// blob detect

vision_methods::vision_methods () {
}

vision_methods::~vision_methods () {
}

cv::Mat vision_methods::preprocessing (const cv::Mat image_in) {
    cv::Mat image_out;
    cvtColor (image_in, image_out, CV_BGR2GRAY);
    cv::GaussianBlur (image_out, image_out, cv::Size (21, 21), 2, 2);
    return image_out;
}
