#include "vision_methods.hpp"

vision_methods::vision_methods () {
    std::cout << "vision_methods constructor" << std::endl;
}

vision_methods::~vision_methods () {
}

cv::Mat vision_methods::preprocessing (const cv::Mat image_in) {
    return image_in;
}
