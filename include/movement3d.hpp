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
     * rotation in z direction
     * @param z rotation matrix
     */
    void rot_z (const cv::Mat& z);

    /**
     * rotation in z direction
     * @return z rotation matrix
     */
    cv::Mat rot_z ();

    void trans_x (const float translation_x);
    float trans_x ();
    void trans_y (const float translation_y);
    float trans_y ();

    void scale (const float scale);
    float scale ();
};

#endif // movement3d_HPP
