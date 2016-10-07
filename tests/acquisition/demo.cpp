#include "acquisition.hpp"

int main (int argc, char const* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: acquisition_test image video cam_id" << std::endl;
        exit (EXIT_FAILURE);
    }
    std::string input_img = argv[1];
    std::string input_vid = argv[2];
    int input_cam         = std::stoi (argv[3]);
    acquisition acquisition_test;
    // set camera source in range
    // set camera source out of range and catch exception
    acquisition_test.source (acquisition_test.cam_count () - 1);
    try {
        acquisition_test.source (acquisition_test.cam_count ());
    } catch (const std::range_error error) {
        std::cout << "---------- source gave me something!" << std::endl;
    }
    std::cout << "cam count is: " << acquisition_test.cam_count () << std::endl;
    acquisition_test.source (input_img);
    cv::imshow ("input img", acquisition_test.capture ());
    cv::waitKey (0);
    acquisition_test.source (input_vid);
    cv::imshow ("input vid", acquisition_test.capture ());
    cv::waitKey (0);
    acquisition_test.source (input_cam);
    cv::imshow ("input cam", acquisition_test.capture ());
    cv::waitKey (0);
    return EXIT_SUCCESS;
}
