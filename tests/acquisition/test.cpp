#include "acquisition.hpp"
#include <fstream>
#include <opencv2/ts/ts.hpp>

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif
CV_TEST_MAIN (".");

TEST (acquisition_cam_count, acquisition) {
    acquisition ac_test;
    ASSERT_EQ (ac_test.cam_count (), 10);
}

TEST (acquisition_file_fail, acquisition) {
    acquisition ac_test;
    ASSERT_THROW (ac_test.source ("./random_file"), std::ifstream::failure);
}

TEST (acquisition_file_no_fail_video, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (
    std::string (SAMPLES_DIR) + std::string ("/3_marker_with_border.webm")));
}

TEST (acquisition_file_no_fail_image, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (
    std::string (SAMPLES_DIR) + std::string ("/arctichare.png")));
}

TEST (acquisition_capture_file_set, acquisition) {
    acquisition ac_test;
    ASSERT_NO_THROW (ac_test.source (
    std::string (SAMPLES_DIR) + std::string ("/arctichare.png")));
    ASSERT_NO_THROW (ac_test.capture ());
}

TEST (acquisition_capture_file_wrong_set, acquisition) {
    acquisition ac_test;
    ASSERT_THROW (ac_test.source ("./random_file"), std::ifstream::failure);
    ASSERT_THROW (ac_test.capture (), std::runtime_error);
}
