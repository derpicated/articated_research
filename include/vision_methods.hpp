#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include <opencv2/opencv.hpp>

class vision_methods {
    private:
    const int _ksize_x = 21;
    const int _ksize_y = 21;
    const int _sigma_x = 2;
    const int _sigma_y = 2;
    std::map<unsigned int, cv::KeyPoint> _reference_markers = {};

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
    std::map<unsigned int, cv::KeyPoint> set_reference (cv::Mat& image_reference);

    /**
     * set the reference from key points
     * @param markers are the reference markers
     * @return returns the reference markers
     */
    std::map<unsigned int, cv::KeyPoint> set_reference_keypoints (
    const std::map<unsigned int, cv::KeyPoint>& markers);

    /**
     * classify the markers and calculate the rotation of the image
     * @param markers are the key points (the marker locations)
     */
    void classification (const std::map<unsigned int, cv::KeyPoint>& markers);
};


#endif // VISION_METHODS_HPP
