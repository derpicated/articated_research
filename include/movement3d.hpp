#ifndef movement3d_HPP
#define movement3d_HPP

#include <GL/gl.h>
#include <opencv2/opencv.hpp>

class movement3d {
    private:
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

    /**
     * convert 3x3 opencv matrix to a 4x4 opengl matrix
     * @param  matrix 3x3 opencv matrix
     * @param gl is the output GLfloat array[movement3d::GL44_SIZE]
     * (size won't be checked!)
     */
    void mat33_to_glfloat44 (cv::Mat& mat, GLfloat gl[GL44_SIZE]);

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
    float translation_delta_to_absolute (float d_value,
    int ref_width,
    float t_min = -1.0,
    float t_max = 1.0);

    /**
     * rotation in x direction
     * @param x rotation matrix
     */
    void rot_x (const cv::Mat& x);

    /**
     * rotation in x direction
     * @return x rotation matrix
     */
    cv::Mat rot_x ();

    /**
     * rotation in x direction
     * @param gl is the output array
     */
    void rot_x_gl (GLfloat gl[GL44_SIZE]);

    /**
     * rotation in y direction
     * @param y rotation matrix
     */
    void rot_y (const cv::Mat& y);

    /**
     * rotation in y direction
     * @return y rotation matrix
     */
    cv::Mat rot_y ();

    /**
     * rotation in y direction
     * @param gl is the output array
     */
    void rot_y_gl (GLfloat gl[GL44_SIZE]);

    /**
     * rotation in z direction
     * @param z rotation matrix
     */
    void rot_z (const cv::Mat& z);

    /**
     * rotation in z direction
     * @return z rotation matrix
     */
    cv::Mat rot_z ();

    /**
     * rotation in z direction
     * @param gl is the output array
     */
    void rot_z_gl (GLfloat gl[GL44_SIZE]);

    void trans_x (const float translation_x);
    float trans_x ();
    void trans_y (const float translation_y);
    float trans_y ();

    void scale (const float scale);
    float scale ();
};

#endif // movement3d_HPP
