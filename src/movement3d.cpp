#include "movement3d.hpp"
#include <opencv2/opencv.hpp>

movement3d::movement3d () {
}
movement3d::~movement3d () {
}

// rotation
void movement3d::rot_x (const cv::Mat& x) {
    _rotation_x = x;
}
cv::Mat movement3d::rot_x () {
    return _rotation_x;
}

void movement3d::rot_y (const cv::Mat& y) {
    _rotation_y = y;
}
cv::Mat movement3d::rot_y () {
    return _rotation_y;
}

void movement3d::rot_z (const cv::Mat& z) {
    _rotation_z = z;
}
cv::Mat movement3d::rot_z () {
    return _rotation_z;
}

// translation
void movement3d::trans_x (const float translation_x) {
    _translation_x = translation_x;
}
float movement3d::trans_x () {
    return _translation_x;
}
void movement3d::trans_y (const float translation_y) {
    _translation_y = translation_y;
}
float movement3d::trans_y () {
    return _translation_y;
}

// scale
void movement3d::scale (const float scale) {
    _scale = scale;
}
float movement3d::scale () {
    return _scale;
}
