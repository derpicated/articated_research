#ifndef VISION_METHODS_HPP
#define VISION_METHODS_HPP

#include <opencv/cv.h>

class vision_methods {
    private:
    /* data */
    public:
    vision_methods ();
    virtual ~vision_methods ();

    cv::Mat preprocessing (const cv::Mat image_in);
};


#endif // VISION_METHODS_HPP
