#include "movement3d.hpp"
#include <GL/gl.h>
#include <iostream>
#include <opencv2/opencv.hpp>

movement3d::movement3d ()
: _translation_x (0.0)
, _translation_y (0.0)
, _scale (0.0) {
    rot_x (rotation_empty);
    rot_y (rotation_empty);
    rot_z (rotation_empty);
}
movement3d::~movement3d () {
}

// conversion of matrix
void movement3d::mat33_to_glfloat44 (const cv::Mat& mat, GLfloat gl[16]) const {
    // check size (else throw)
    // I cant check array's size when I only have a pointer
    if ((mat.rows != 3) || (mat.cols != 3)) {
        throw std::length_error ("matrix needs to be of size 3x3");
    }
    // check type
    cv::Mat mat32f;
    mat.convertTo (mat32f, CV_32F);
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
    gl[0] = mat32f.at<float> (cv::Point (0, 0));
    gl[1] = mat32f.at<float> (cv::Point (1, 0));
    gl[2] = mat32f.at<float> (cv::Point (2, 0));
    gl[3] = 0;
    //  e f g 0
    gl[4] = mat32f.at<float> (cv::Point (0, 1));
    gl[5] = mat32f.at<float> (cv::Point (1, 1));
    gl[6] = mat32f.at<float> (cv::Point (2, 1));
    gl[7] = 0;
    // i j k 0
    gl[8]  = mat32f.at<float> (cv::Point (0, 2));
    gl[9]  = mat32f.at<float> (cv::Point (1, 2));
    gl[10] = mat32f.at<float> (cv::Point (2, 2));
    gl[11] = 0;
    // 0 0 0 1
    gl[12] = 0;
    gl[13] = 0;
    gl[14] = 0;
    gl[15] = 1;
}

float movement3d::translation_delta_to_absolute (const float d_value,
const int ref_width,
const float t_min,
const float t_max) const {
    return (((t_max - t_min) * d_value) / ref_width);
}

// rotation
void movement3d::rot_x (const cv::Mat& x) {
    cv::Mat mat32f;
    x.convertTo (mat32f, CV_32F);
    _rotation_x = mat32f;
}
cv::Mat movement3d::rot_x () const {
    return _rotation_x;
}
void movement3d::rot_x_gl (GLfloat gl[GL44_SIZE]) const {
    mat33_to_glfloat44 (_rotation_x, gl);
}

void movement3d::rot_y (const cv::Mat& y) {
    cv::Mat mat32f;
    y.convertTo (mat32f, CV_32F);
    _rotation_y = mat32f;
}
cv::Mat movement3d::rot_y () const {
    return _rotation_y;
}
void movement3d::rot_y_gl (GLfloat gl[GL44_SIZE]) const {
    mat33_to_glfloat44 (_rotation_y, gl);
}

void movement3d::rot_z (const cv::Mat& z) {
    cv::Mat mat32f;
    z.convertTo (mat32f, CV_32F);
    _rotation_z = mat32f;
}
cv::Mat movement3d::rot_z () const {
    return _rotation_z;
}
void movement3d::rot_z_gl (GLfloat gl[GL44_SIZE]) const {
    mat33_to_glfloat44 (_rotation_z, gl);
}

// translation
void movement3d::trans_x (const float translation_x) {
    _translation_x = translation_x;
}
float movement3d::trans_x () const {
    return _translation_x;
}
void movement3d::trans_y (const float translation_y) {
    _translation_y = translation_y;
}
float movement3d::trans_y () const {
    return _translation_y;
}

// scale
void movement3d::scale (const float scale) {
    _scale = scale;
}
float movement3d::scale () const {
    return _scale;
}

std::ostream& operator<< (std::ostream& os, const movement3d& movement) {
    os << "rot x[cv::Mat]: " << movement.rot_x () << std::endl;
    os << "rot y[cv::Mat]: " << movement.rot_y () << std::endl;
    os << "rot z[cv::Mat]: " << movement.rot_z () << std::endl;
    os << std::endl;

    GLfloat gl[movement3d::GL44_SIZE];
    os << "rot x GL: " << std::endl;
    movement.rot_x_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        os << gl[i] << ", ";
    }
    os << std::endl;
    os << "rot y GL: " << std::endl;
    movement.rot_y_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        os << gl[i] << ", ";
    }
    os << std::endl;
    os << "rot z GL: " << std::endl;
    movement.rot_z_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        os << gl[i] << ", ";
    }
    os << std::endl;
    os << std::endl;

    os << "translation x: " << movement.trans_x () << std::endl;
    os << "translation y: " << movement.trans_y () << std::endl;
    os << std::endl;

    os << "scale: " << movement.scale () << std::endl;
    return os;
}

movement3d& movement3d::operator+= (const movement3d& movement) {
    this->rot_x (this->rot_x () + movement.rot_x ());
    this->rot_y (this->rot_y () + movement.rot_y ());
    this->rot_z (this->rot_z () + movement.rot_z ());

    this->trans_x (this->trans_x () + movement.trans_x ());
    this->trans_y (this->trans_y () + movement.trans_y ());

    this->scale (this->scale () + movement.scale ());

    return *this;
}

movement3d movement3d::operator+ (const movement3d& movement) {
    *this += movement;
    return *this;
}

movement3d& movement3d::operator/= (const int factor) {
    this->rot_x (this->rot_x () / factor);
    this->rot_y (this->rot_y () / factor);
    this->rot_z (this->rot_z () / factor);

    this->trans_x (this->trans_x () / factor);
    this->trans_y (this->trans_y () / factor);

    this->scale (this->scale () / factor);

    return *this;
}

movement3d movement3d::operator/ (const int factor) {
    *this /= factor;
    return *this;
}
