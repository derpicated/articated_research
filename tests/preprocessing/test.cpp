#include "acquisition.hpp"
#include "vision_methods.hpp"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/ts.hpp>

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif

CV_TEST_MAIN (".");

TEST (preprocessing_image_no_fail_video, preprocessing) {
    acquisition ac_test;
    vision_methods vm_test;
    cv::Mat image;
    ASSERT_NO_THROW (ac_test.source (
    std::string (SAMPLES_DIR) + std::string ("/3_markers_good.webm")))
    << "the sample video file cannot be read";
    ASSERT_NO_THROW (image = ac_test.capture ())
    << "the file cannot be captured";
    ASSERT_NO_THROW (image = vm_test.preprocessing (image))
    << "preprocessing did oops";
}

TEST (preprocessing_image_no_fail_image, preprocessing) {
    acquisition ac_test;
    vision_methods vm_test;
    cv::Mat image;
    ASSERT_NO_THROW (ac_test.source (std::string (SAMPLES_DIR) + std::string ("/arctichare.png")))
    << "the sample video file cannot be read";
    ASSERT_NO_THROW (image = ac_test.capture ())
    << "the file cannot be captured";
    ASSERT_NO_THROW (image = vm_test.preprocessing (image))
    << "preprocessing did oops";
}
