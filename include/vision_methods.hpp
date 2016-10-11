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
     * remove background and transform to binary image.
     * @param  image_in image to be segmented
     * @return          segmented image
     */
    void extraction (const cv::Mat& image_in, std::map<unsigned int, cv::KeyPoint>&);
    // structure? feature_extraction(const cv::Mat&image_in);
    // map? classification (const ...);
};


#endif // VISION_METHODS_HPP
