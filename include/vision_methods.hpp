#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include <map>
#include <opencv2/opencv.hpp>

class vision_methods {
    private:
    const int _ksize_x = 21;
    const int _ksize_y = 21;
    const int _sigma_x = 2;
    const int _sigma_y = 2;
    const int _blob_size_ratio = 2; // ration between size and whitespace
    /**
     * extract markers from a map of features
     * @param    points a vector of features
     * @param    markers a map of MarkerID, MarkerLocation
     * @return
     */
    void extract_markers (std::vector<cv::KeyPoint>& key_points,
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
    // structure? feature_extraction(const cv::Mat&image_in);
    // map? classification (const ...);
};


#endif // VISION_METHODS_HPP
