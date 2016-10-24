#ifndef movement3d_HPP
#define movement3d_HPP

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
    movement3d ();
    ~movement3d ();

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
