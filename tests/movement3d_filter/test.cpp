#include "movement3d.hpp"
#include "movement3d_filter.hpp"
#include <opencv2/ts.hpp>

CV_TEST_MAIN (".");

TEST (movement3d_filter_average_two_nofail, movement3d_filter) {
    movement3d_average filter (2);
    movement3d x1, x2, av;
    // clang-format off
    float x1_rot_val[9] = {
        0.0, 0.1, 0.2,
        0.3, 0.4, 0.5,
        0.6, 0.7, 0.8
    };
    float x2_rot_val[9] = {
        0.2, 0.3, 0.4,
        0.5, 0.6, 0.7,
        0.8, 0.9, 1.0
    };
    // clang-format on
    cv::Mat x1_rot = cv::Mat (3, 3, CV_32F, x1_rot_val);
    cv::Mat x2_rot = cv::Mat (3, 3, CV_32F, x2_rot_val);

    x1.rot_x (x1_rot);
    x1.rot_y (x1_rot);
    x1.rot_z (x1_rot);
    x1.trans_x (0.0);
    x1.trans_y (0.1);
    x1.scale (0.2);

    x2.rot_x (x2_rot);
    x2.rot_y (x2_rot);
    x2.rot_z (x2_rot);
    x2.trans_x (0.2);
    x2.trans_y (0.3);
    x2.scale (0.4);

    filter.average (x1);
    filter.average (x2);
    av = filter.average ();

    // rot x
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 0)), 0.2);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 1)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 1)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 2)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 2)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 2)), 0.9);
    // rot y
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 0)), 0.2);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 1)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 1)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 2)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 2)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 2)), 0.9);
    // rot z
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 0)), 0.1);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 0)), 0.2);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 1)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 1)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 2)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 2)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 2)), 0.9);

    ASSERT_FLOAT_EQ (av.trans_x (), 0.1);
    ASSERT_FLOAT_EQ (av.trans_y (), 0.2);

    ASSERT_FLOAT_EQ (av.scale (), 0.3);
}

TEST (movement3d_filter_average_four_nofail, movement3d_filter) {
    movement3d_average filter (4);
    movement3d x1, x2, x3, x4, av;
    // clang-format off
    float x1_rot_val[9] = {
        0.0, 0.1, 0.2,
        0.3, 0.4, 0.5,
        0.6, 0.7, 0.8
    };
    float x2_rot_val[9] = {
        0.2, 0.3, 0.4,
        0.5, 0.6, 0.7,
        0.8, 0.9, 1.0
    };
    float x3_rot_val[9] = {
        0.4, 0.5, 0.6,
        0.7, 0.8, 0.9,
        1.0, 1.1, 1.2
    };
    float x4_rot_val[9] = {
        0.6, 0.7, 0.8,
        0.9, 1.0, 1.1,
        1.2, 1.3, 1.4
    };
    // clang-format on
    cv::Mat x1_rot = cv::Mat (3, 3, CV_32F, x1_rot_val);
    cv::Mat x2_rot = cv::Mat (3, 3, CV_32F, x2_rot_val);
    cv::Mat x3_rot = cv::Mat (3, 3, CV_32F, x3_rot_val);
    cv::Mat x4_rot = cv::Mat (3, 3, CV_32F, x4_rot_val);

    x1.rot_x (x1_rot);
    x1.rot_y (x1_rot);
    x1.rot_z (x1_rot);
    x1.trans_x (0.0);
    x1.trans_y (0.1);
    x1.scale (0.2);

    x2.rot_x (x2_rot);
    x2.rot_y (x2_rot);
    x2.rot_z (x2_rot);
    x2.trans_x (0.2);
    x2.trans_y (0.3);
    x2.scale (0.4);

    x3.rot_x (x3_rot);
    x3.rot_y (x3_rot);
    x3.rot_z (x3_rot);
    x3.trans_x (0.4);
    x3.trans_y (0.5);
    x3.scale (0.6);

    x4.rot_x (x4_rot);
    x4.rot_y (x4_rot);
    x4.rot_z (x4_rot);
    x4.trans_x (0.6);
    x4.trans_y (0.7);
    x4.scale (0.8);

    filter.average (x1);
    filter.average (x2);
    filter.average (x3);
    filter.average (x4);
    av = filter.average ();

    // rot x
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 0)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 1)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 1)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (0, 2)), 0.9);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (1, 2)), 1.0);
    ASSERT_FLOAT_EQ (av.rot_x ().at<float> (cv::Point (2, 2)), 1.1);
    // rot y
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 0)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 1)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 1)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (0, 2)), 0.9);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (1, 2)), 1.0);
    ASSERT_FLOAT_EQ (av.rot_y ().at<float> (cv::Point (2, 2)), 1.1);
    // rot z
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 0)), 0.3);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 0)), 0.4);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 0)), 0.5);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 1)), 0.6);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 1)), 0.7);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 1)), 0.8);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (0, 2)), 0.9);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (1, 2)), 1.0);
    ASSERT_FLOAT_EQ (av.rot_z ().at<float> (cv::Point (2, 2)), 1.1);

    ASSERT_FLOAT_EQ (av.trans_x (), 0.3);
    ASSERT_FLOAT_EQ (av.trans_y (), 0.4);

    ASSERT_FLOAT_EQ (av.scale (), 0.5);
}
