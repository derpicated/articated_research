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

// source ...
// <http://stackoverflow.com/questions/35942095/opencv-strange-rotation-and-translation-matrices-from-decomposehomographymat>

int main () {
    std::cout << "classification demo" << std::endl;

    // read sample image
    cv::Mat image = cv::imread (std::string (SAMPLES_DIR) +
    std::string ("/perspective_transform_straight.png"));
    cv::Size size (image.size ());
    cv::Mat output_image (size, 0);

    // set up a virtual camera
    float f = 100, w = 500, h = 500;

    // |fx 0  cx| (cx, cy) is a principal point
    // |0  fy cy|          that is usually at the image center
    // |0  0  1 | (fx, fy) are the focal lengths expressed in pixel units.
    cv::Mat1f K = (cv::Mat1f (3, 3) << f, 0, w / 2, 0, f, h / 2, 0, 0, 1);

    // set transformation from 1st to 2nd camera (assume K is unchanged)
    // cv::Mat1f rvecDeg = (cv::Mat1f (3, 1) << 45, 0, 0);
    // cv::Mat1f t       = (cv::Mat1f (3, 1) << 0, 0, 0);

    // known points on reference {x, y}
    // X   X
    //
    // X   X
    std::vector<cv::Point2f> input = { { 0, 0 }, { 4, 0 }, { 0, 4 }, { 4, 4 } };
    // destination
    // X   X
    // X   X
    std::vector<cv::Point2f> dest = { { 0, 0 }, { 4, 0 }, { 0, 2.828427125 },
        { 4, 2.828427125 } };
    // somewhat of an 45 degrees angle

    // find homography beteen images
    cv::Mat H = cv::findHomography (input, dest);

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Estimated H = \n" << H << std::endl << std::endl;

    // decompose and find information that is in the transformation matrix
    std::vector<cv::Mat> rotations, translations, normals;
    cv::decomposeHomographyMat (H, K, rotations, translations, normals);

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Estimated decomposition:" << std::endl;
    std::cout << "rotations (cv::Rodrigues)= " << std::endl;
    for (auto r : rotations) {
        cv::Mat1d rvec;
        cv::Rodrigues (r, rvec);
        std::cout << rvec * 180 / CV_PI << std::endl << std::endl;
    }

    std::cout << "rotations = " << std::endl;
    for (auto r : rotations) {
        std::cout << r << std::endl;
    }

    std::cout << std::endl;

    std::cout << "translations = " << std::endl;
    for (auto t : translations) {
        std::cout << t << std::endl << std::endl;
    }

    std::cout << std::endl;

    std::cout << "normals = " << std::endl;
    for (auto n : normals) {
        std::cout << n << std::endl << std::endl;
    }

    // transform and display image * H = output in 2D
    cv::warpPerspective (image, output_image, H, size);
    cv::imshow ("outputImage", output_image);
    cv::waitKey (0);
    return EXIT_SUCCESS;
}
