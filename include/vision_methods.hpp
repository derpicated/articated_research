#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include <opencv/cv.h>

class vision_methods {
    private:
    const int _ksize_x = 21;
    const int _ksize_y = 21;
    const int _sigma_x = 2;
    const int _sigma_y = 2;

    public:
    vision_methods ();
    virtual ~vision_methods ();

    /**
     * preprocess image
     * - greyscale
     * - blur to remove noise
     * @param  image_in image in
     * @return image out
     */
    cv::Mat preprocessing (const cv::Mat image_in);
};


#endif // VISION_METHODS_HPP
