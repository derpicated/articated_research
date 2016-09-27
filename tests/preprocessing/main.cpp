#include "vision_methods.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * Test the vison method preprocessing
 */
int main (int argc, char const* argv[]) {
    if (argc != 2) {
        std::cout << " Usage: preprocessing_test image" << std::endl;
        return -1;
    }
    std::cout << "preprocessing test" << std::endl;

    cv::Mat image_in, image_out;
    vision_methods preprocessing_test;
    image_in = cv::imread (argv[1], CV_LOAD_IMAGE_COLOR); // Read the file

    if (!image_in.data) {
        std::cout << "could not open or find the image" << std::endl;
        return -1;
    }
    image_out = preprocessing_test.preprocessing (image_in);

    // cv::namedWindow (
    //"Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow ("input", image_in);   // Show our image inside it.
    cv::imshow ("output", image_out); // Show our image inside it.
    cv::moveWindow (
    "output", image_out.size ().width, 0); // just move it to the "next" window
    cv::waitKey (0);                       // Wait for a keystroke in the window
    return 0;
}
