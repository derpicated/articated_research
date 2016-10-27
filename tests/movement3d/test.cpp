#include "movement3d.hpp"
#include <opencv2/ts.hpp>

CV_TEST_MAIN (".");

TEST (movement3d_mat33_to_glfloat44_nofail, movement3d) {
    movement3d movement3d_test;
    // clang-format off
    // total
    float t[16] = {
        0.1, 0.2, 0.3, 0,
        0.4, 0.5, 0.6, 0,
        0.7, 0.8, 0.9, 0,
          0,   0,   0, 1
    };
    float in_val[9] = {
        t[0], t[1], t[2],
        t[4], t[5], t[6],
        t[8], t[9], t[10]
    };
    // clang-format on

    cv::Mat in = cv::Mat (3, 3, CV_32F, in_val);
    GLfloat out[movement3d::GL44_SIZE];

    movement3d_test.mat33_to_glfloat44 (in, out);

    for (unsigned int i = 0; i < sizeof (t) / sizeof (t[0]); i++) {
        ASSERT_EQ (t[i], out[i]) << "matrix not copied over correctly!";
    }
}

TEST (movement3d_translation_delta_to_absolute_nofail, movement3d) {
    movement3d movement3d_test;
    //          x         no movement (delta is 0)
    // -1       0        1
    // | ------ | ------ |
    ASSERT_FLOAT_EQ (movement3d_test.translation_delta_to_absolute (0, 100, -1.0, 1.0), 0);

    //          x -->10   10 points to right
    // -1       0        1
    // | ------ | ------ |
    ASSERT_FLOAT_EQ (
    movement3d_test.translation_delta_to_absolute (10, 100, -1.0, 1.0), 0.2);

    //    10<-- x         10 points to left
    // -1       0        1
    // | ------ | ------ |
    ASSERT_FLOAT_EQ (
    movement3d_test.translation_delta_to_absolute (-10, 100, -1.0, 1.0), -0.2);

    //          x -->50   50 points to right
    // -1       0        1
    // | ------ | ------ |
    ASSERT_FLOAT_EQ (
    movement3d_test.translation_delta_to_absolute (50, 100, -1.0, 1.0), 1.0);


    //    50<-- x         50 points to left
    // -1       0        1
    // | ------ | ------ |
    ASSERT_FLOAT_EQ (
    movement3d_test.translation_delta_to_absolute (-50, 100, -1.0, 1.0), -1.0);
}
