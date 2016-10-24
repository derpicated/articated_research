#include "vision_methods.hpp"
#include "movement3d.hpp"
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

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const cv::Mat& image_reference) {
    (void)image_reference;
    throw std::runtime_error (
    "missing implementation of set_reference from image");
    return {};
}

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const std::map<unsigned int, cv::Point2f>& markers) {
    if (markers.size () < _minimal_ref_points) {
        throw std::length_error ("too few reference points");
    }
    _reference_markers = markers;
    return _reference_markers;
}

movement3d classification (const std::map<unsigned int, cv::Point2f>& markers) {
    (void)markers;
    movement3d movement;
    return movement;
}
