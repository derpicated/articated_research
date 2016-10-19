#include "vision_methods.hpp"
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif

int main () {
    std::cout << "classification demo" << std::endl;
    // findHomography(InputArray srcPoints, InputArray dstPoints, int method=0,
    // double ransacReprojThreshold=3, OutputArray mask=noArray() )
    // pt(10, 20)
    std::vector<cv::Point2f> input = { cv::Point2f (91, 81),
        cv::Point2f (409, 81), cv::Point2f (91, 376), cv::Point2f (409, 376) };
    std::vector<cv::Point2f> destination = { cv::Point2f (88, 154),
        cv::Point2f (357, 201), cv::Point2f (102, 432), cv::Point2f (401, 449) };
    cv::Mat output;
    output = cv::findHomography (input, destination);
    std::cout << output << std::endl;


    cv::Mat image = cv::imread (std::string (SAMPLES_DIR) +
    std::string ("/perspective_transform_straight.png"));
    cv::Size size (image.size ());
    cv::Mat output_image (size, 0);
    cv::warpPerspective (image, output_image, output, size);

    cv::imshow ("outputImage", output_image);

    cv::resize (output, output, { 100, 100 });
    cv::imshow ("output img", output);
    cv::waitKey (0);
    return EXIT_SUCCESS;
}
