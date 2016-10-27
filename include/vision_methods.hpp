#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include "movement3d.hpp"
#include <opencv2/opencv.hpp>

class vision_methods {
    private:
    const int _ksize_x                     = 21;
    const int _ksize_y                     = 21;
    const int _sigma_x                     = 2;
    const int _sigma_y                     = 2;
    const unsigned int _minimal_ref_points = 2;
    std::map<unsigned int, cv::Point2f> _reference_markers = {};
    // set up a virtual camera
    const float _f = 100, _w = 500, _h = 500;
    // intrinsic camera matrix
    // |fx 0  cx| (cx, cy) is a principal point
    // |0  fy cy|          that is usually at the image center
    // |0  0  1 | (fx, fy) are the focal lengths expressed in pixel units.
    // clang-format off
    cv::Mat1f _K = (cv::Mat1f (3, 3) <<
        _f, 0,  _w/2,
        0,  _f, _h/2,
        0,  0,  1   );
    // clang-format on

    public:
    vision_methods ();
    ~vision_methods ();

    /**
     * preprocess image
     * - greyscale
     * - blur to remove noise
     * @param  image_in image in
     * @return image out
     */
    cv::Mat preprocessing (const cv::Mat& image_in);

    /**
     * segment image
     * remove background and transform to binary image.
     * @param  image_in image to be segmented
     * @return          segmented image
     */
    cv::Mat segmentation (const cv::Mat& image_in);

    /**
     * set the reference from image
     * @param image_reference the reference image
     * @return returns the reference that is stored
     */
    std::map<unsigned int, cv::Point2f> set_reference (const cv::Mat& image_reference);

    /**
     * set the reference from key points
     * @param markers are the reference markers
     * @return returns the reference markers
     */
    std::map<unsigned int, cv::Point2f> set_reference (
    const std::map<unsigned int, cv::Point2f>& markers);

    /**
     * classify the markers and calculate the movement of the image
     * @param  image the image that needs comparison to reference
     * @return returns the movement
     */
    movement3d classification (const cv::Mat& image);

    /**
     * classify the markers and calculate the movement of the image
     * @param markers are the key points (the marker locations)
     * @return returns the movement
     */
    movement3d classification (const std::map<unsigned int, cv::Point2f>& markers);
};


#endif // VISION_METHODS_HPP
