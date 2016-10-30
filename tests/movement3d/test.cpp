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

TEST (movement3d_operator_plus_no_fail, movement3d) {
    movement3d x1, x2, compare;
    // clang-format off
    float x1_rot_val[9] = {
        0.1, 0.2, 0.3,
        0.4, 0.5, 0.6,
        0.7, 0.8, 0.9
    };
    float x2_rot_val[9] = {
        0.0, 0.1, 0.2,
        0.3, 0.4, 0.5,
        0.6, 0.7, 0.8
    };
    // clang-format on
    cv::Mat x1_rot = cv::Mat (3, 3, CV_32F, x1_rot_val);
    cv::Mat x2_rot = cv::Mat (3, 3, CV_32F, x2_rot_val);

    x1.rot_x (x1_rot);
    x1.rot_y (x1_rot);
    x1.rot_z (x1_rot);
    x1.trans_x (1.1);
    x1.trans_y (1.2);
    x1.scale (1.3);

    x2.rot_x (x2_rot);
    x2.rot_y (x2_rot);
    x2.rot_z (x2_rot);
    x2.trans_x (2.1);
    x2.trans_y (2.2);
    x2.scale (2.3);

    compare = x1 + x2;
    // rot x
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (1, 0)), 0.3);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (0, 1)), 0.7);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (1, 1)), 0.9);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (2, 1)), 1.1);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (0, 2)), 1.3);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (1, 2)), 1.5);
    ASSERT_FLOAT_EQ (compare.rot_x ().at<float> (cv::Point (2, 2)), 1.7);
    // rot y
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (1, 0)), 0.3);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (0, 1)), 0.7);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (1, 1)), 0.9);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (2, 1)), 1.1);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (0, 2)), 1.3);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (1, 2)), 1.5);
    ASSERT_FLOAT_EQ (compare.rot_y ().at<float> (cv::Point (2, 2)), 1.7);
    // rot z
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (1, 0)), 0.3);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (0, 1)), 0.7);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (1, 1)), 0.9);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (2, 1)), 1.1);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (0, 2)), 1.3);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (1, 2)), 1.5);
    ASSERT_FLOAT_EQ (compare.rot_z ().at<float> (cv::Point (2, 2)), 1.7);

    ASSERT_FLOAT_EQ (compare.trans_x (), 3.2);
    ASSERT_FLOAT_EQ (compare.trans_y (), 3.4);

    ASSERT_FLOAT_EQ (compare.scale (), 3.6);
}
