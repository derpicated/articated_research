#include "acquisition.hpp"

// small demo to show some features
int main (int argc, char const* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: acquisition_demo image video cam_id" << std::endl;
        exit (EXIT_FAILURE);
    }
    std::string input_img = argv[1];
    std::string input_vid = argv[2];
    int input_cam         = std::stoi (argv[3]);
    acquisition acquisition_test;
    std::cout << "camera count is: " << acquisition_test.cam_count () << std::endl;
    // show image
    acquisition_test.source (input_img);
    cv::imshow ("input img", acquisition_test.capture ());
    cv::waitKey (0);
    cv::destroyAllWindows ();
    // show video
    acquisition_test.source (input_vid);
    cv::imshow ("input vid", acquisition_test.capture ());
    cv::waitKey (0);
    // show camera
    acquisition_test.source (input_cam);
    cv::imshow ("input cam", acquisition_test.capture ());
    cv::waitKey (0);
    return EXIT_SUCCESS;
}
