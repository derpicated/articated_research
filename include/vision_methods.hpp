#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include <map>
#include <opencv2/opencv.hpp>

class vision_methods {
    private:
    const int _ksize_x                = 21;
    const int _ksize_y                = 21;
    const int _sigma_x                = 2;
    const int _sigma_y                = 2;
    const unsigned int _MIN_MARKER_ID = 2;
    const unsigned int _MAX_MARKER_ID = 9;
    const int _BLOB_SIZE_RATIO        = 4; // ratio between size and whitespace
    std::map<unsigned int, cv::KeyPoint> _reference_markers = {};

    /**
    * find groups from a vector of keypoints, based on proximity
    * @param    key_points a vector of features
    * @param    potential_markers ouptut containing groups of points
    * @return
    */
    void extract_groups (std::vector<cv::KeyPoint> key_points,
    std::vector<std::vector<cv::KeyPoint>>& potential_markers);

    /**
    * recursively link all blobs in group
    * @param    neighbours contains all grouped neighbours per KeyPoint
    * @param    potential_marker contains all blobs for one potential marker
    * @param    point the keypoint thats under inspection
    * @return
    */
    void extract_groups_link (std::map<cv::KeyPoint, std::vector<cv::KeyPoint>>& neighbours,
    std::vector<cv::KeyPoint>& potential_marker,
    const cv::KeyPoint& point);

    /**
    * extract markers from a vector of marker candidates
    * @param    potential_markers a vector of groups of keypoints
    * @param    markers output map of MarkerID, MarkerLocation
    * @return
    */
    void extract_markers (std::vector<std::vector<cv::KeyPoint>>& potential_markers,
    std::map<unsigned int, cv::Point2f>& markers);

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
     * extract features image
     * @param  image_in image to be segmented
     * @param  markers output map for found markers
     * @return          segmented image
     */
    cv::Mat extraction (const cv::Mat& image_in, std::map<unsigned int, cv::Point2f>& markers);
    
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
