#include "acquisition.hpp"
#include <fstream>
#include <opencv2/ts.hpp>

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif
CV_TEST_MAIN (".");

TEST (acquisition_cam_count, acquisition) {
    acquisition ac_test;
    ASSERT_EQ (ac_test.cam_count (), 10) << "camera count is wrong";
}

TEST (acquisition_file_fail, acquisition) {
    acquisition ac_test;
    ASSERT_THROW (ac_test.source ("./random_file"), std::ifstream::failure)
    << "a random file that doesn't exist should throw an error";
}

TEST (acquisition_file_no_fail_video, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (
    std::string (SAMPLES_DIR) + std::string ("/3_marker_with_border.webm")))
    << "the sample video file cannot be read";
}

TEST (acquisition_file_no_fail_image, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (std::string (SAMPLES_DIR) + std::string ("/arctichare.png")))
    << "the sample image file cannot be read";
}

TEST (acquisition_capture_file_set, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (std::string (SAMPLES_DIR) + std::string ("/arctichare.png")))
    << "the sample file cannot be read";
    ASSERT_NO_THROW (ac_test.capture ()) << "the file cannot be captured";
}

TEST (acquisition_capture_file_wrong_set, acquisition) {
    acquisition ac_test;
    ASSERT_THROW (ac_test.source ("./random_file"), std::ifstream::failure)
    << "the file does not exists, so an error should be thrown";
    ASSERT_THROW (ac_test.capture (), std::runtime_error)
    << "the file is not set correctly, so an error should be thrown";
}
