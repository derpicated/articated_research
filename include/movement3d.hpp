#ifndef movement3d_HPP
#define movement3d_HPP

#include <GL/gl.h>
#include <iostream>
#include <opencv2/opencv.hpp>

class movement3d {
    private:
    // clang-format off
    float rotation_empty_val[9] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };
    // clang-format on
    cv::Mat rotation_empty = cv::Mat (3, 3, CV_32F, rotation_empty_val);
    // rotation
    cv::Mat _rotation_x;
    cv::Mat _rotation_y;
    cv::Mat _rotation_z;
    // translation
    float _translation_x;
    float _translation_y;
    // scale
    float _scale;

    public:
    static const unsigned int GL44_SIZE = 16;

    movement3d ();
    ~movement3d ();

    movement3d& operator+= (const movement3d& movement);
    movement3d operator+ (const movement3d& movement);

    movement3d& operator/= (const int factor);
    movement3d operator/ (int factor);

    /**
     * convert 3x3 opencv matrix to a 4x4 opengl matrix
     * @param  matrix 3x3 opencv matrix
     * @param gl is the output GLfloat array[movement3d::GL44_SIZE]
     * (size won't be checked!)
     */
    void mat33_to_glfloat44 (const cv::Mat& mat, GLfloat gl[GL44_SIZE]) const;

    /**
     * convert a translation delta to an absolute value on a plane
     * (t_max - t_min) = steps that can be taken
     * [cross-multiplication]
     * absolute_value   =   steps
     * delta_value      =   ref_width
     * @param  d_value   delta value
     * @param  ref_width reference width (e.g. image width)
     * @param  t_min     translate minimum
     * @param  t_max     translate maximum
     * @return           the absolute value
     */
    float translation_delta_to_absolute (const float d_value,
    const int ref_width,
    const float t_min = -1.0,
    const float t_max = 1.0) const;

    /**
     * rotation in x direction
     * @param x rotation matrix
     */
    void rot_x (const cv::Mat& x);

    /**
     * rotation in x direction
     * @return x rotation matrix
     */
    cv::Mat rot_x () const;

    /**
     * rotation in x direction
     * @param gl is the output array
     */
    void rot_x_gl (GLfloat gl[GL44_SIZE]) const;

    /**
     * rotation in y direction
     * @param y rotation matrix
     */
    void rot_y (const cv::Mat& y);

    /**
     * rotation in y direction
     * @return y rotation matrix
     */
    cv::Mat rot_y () const;

    /**
     * rotation in y direction
     * @param gl is the output array
     */
    void rot_y_gl (GLfloat gl[GL44_SIZE]) const;

    /**
     * rotation in z direction
     * @param z rotation matrix
     */
    void rot_z (const cv::Mat& z);

    /**
     * rotation in z direction
     * @return z rotation matrix
     */
    cv::Mat rot_z () const;

    /**
     * rotation in z direction
     * @param gl is the output array
     */
    void rot_z_gl (GLfloat gl[GL44_SIZE]) const;

    void trans_x (const float translation_x);
    float trans_x () const;
    void trans_y (const float translation_y);
    float trans_y () const;

    void scale (const float scale);
    float scale () const;
};

// operator functions
std::ostream& operator<< (std::ostream& os, const movement3d& movement);

#endif // movement3d_HPP
