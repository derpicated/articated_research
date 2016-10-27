#include "movement3d.hpp"
#include <GL/gl.h>
#include <opencv2/opencv.hpp>

movement3d::movement3d () {
}
movement3d::~movement3d () {
}

// conversion of matrix
void movement3d::mat33_to_glfloat44 (cv::Mat& mat, GLfloat gl[16]) {
    // check size (else throw)
    if ((mat.rows != 3) || (mat.cols != 3)) {
        throw std::length_error ("matrix needs to be of size 3x3");
    }
    // I cant check array's size when I only have a pointer
    /**
     * in: cv::Mat
     * [ a b c
     *   e f g
     *   i j k ]
     * out: GLfloat
     * [ a b c 0
     *   e f g 0
     *   i j k 0
     *   0 0 0 1 ]
     */
    // a b c 0
    gl[0] = mat.at<float> (0, 0);
    gl[1] = mat.at<float> (0, 1);
    gl[2] = mat.at<float> (0, 2);
    gl[3] = 0;
    //  e f g 0
    gl[4] = mat.at<float> (1, 0);
    gl[5] = mat.at<float> (1, 1);
    gl[6] = mat.at<float> (1, 2);
    gl[7] = 0;
    // i j k 0
    gl[8]  = mat.at<float> (2, 0);
    gl[9]  = mat.at<float> (2, 1);
    gl[10] = mat.at<float> (2, 2);
    gl[11] = 0;
    // 0 0 0 1
    gl[12] = 0;
    gl[13] = 0;
    gl[14] = 0;
    gl[15] = 1;
}

// rotation
void movement3d::rot_x (const cv::Mat& x) {
    _rotation_x = x;
}
cv::Mat movement3d::rot_x () {
    return _rotation_x;
}
void movement3d::rot_x_gl (GLfloat gl[GL44_SIZE]) {
    mat33_to_glfloat44 (_rotation_x, gl);
}

void movement3d::rot_y (const cv::Mat& y) {
    _rotation_y = y;
}
cv::Mat movement3d::rot_y () {
    return _rotation_y;
}
void movement3d::rot_y_gl (GLfloat gl[GL44_SIZE]) {
    mat33_to_glfloat44 (_rotation_y, gl);
}

void movement3d::rot_z (const cv::Mat& z) {
    _rotation_z = z;
}
cv::Mat movement3d::rot_z () {
    return _rotation_z;
}
void movement3d::rot_z_gl (GLfloat gl[GL44_SIZE]) {
    mat33_to_glfloat44 (_rotation_z, gl);
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
