#include "acquisition.hpp"
#include <opencv2/ts/ts.hpp>

TEST (acquisition_test, acquisition_cam_count) {
    acquisition ac_test;
    ASSERT_EQ (ac_test.cam_count (), 10);
}

CV_TEST_MAIN (".")
