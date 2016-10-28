#include "vision_methods.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
/**
 * Test the vision method segmentation
 */
int main (int argc, char const* argv[]) {
    // argv 1: type
    // argv 2: data
    if (argc != 3) {
        std::cout << "Usage: segmentation_test date_type date" << std::endl;
        std::cout << "data_type: v = video" << std::endl;
        std::cout << "data_type: i = image" << std::endl;
        std::cout << "data_type: c = camera (file is cam ID)" << std::endl;
        exit (EXIT_FAILURE);
    }

    bool infinite_loop = false;
    cv::VideoCapture cap;
    const std::string type = argv[1];
    const std::string file = argv[2];
    cv::Mat image_in, image_tmp, image_out;
    vision_methods segmentation_test;
    std::chrono::high_resolution_clock::time_point start_time;
    const int fps  = 30;
    unsigned int n = 0, total_count = 0;
    double total_duration = 0;
    std::vector<cv::KeyPoint> key_points;

    switch (type[0]) {
        case 'c':
            if (!cap.open (std::stoi (file))) {
                std::cout << "camera could not be opened" << std::endl;
                exit (EXIT_FAILURE);
            }
            infinite_loop = true;
            break;
        case 'v':
            if (!cap.open ((file))) {
                std::cout << "video could not be opened" << std::endl;
                exit (EXIT_FAILURE);
            }
            n = 100;
            break;
        case 'i':
            image_in = cv::imread (file, CV_LOAD_IMAGE_COLOR);

            if (!image_in.data) {
                std::cout << "could not open or find the image" << std::endl;
                exit (EXIT_FAILURE);
            }
            n = 1;
            break;
        default: std::cout << "not suported" << std::endl; exit (EXIT_FAILURE);
    }

    while (n > 0 || infinite_loop) {
        --n;
        ++total_count;
        if (type == "c" || type == "v") {
            cap >> image_in;
        }

        // actuall test call
        image_tmp  = segmentation_test.preprocessing (image_in);
        start_time = std::chrono::high_resolution_clock::now ();
        image_out  = segmentation_test.segmentation (image_tmp);
        total_duration += std::chrono::duration_cast<std::chrono::microseconds> (
        std::chrono::high_resolution_clock::now () -
        start_time).count ();

        // display test results
        if (!image_in.empty ()) {
            cv::imshow ("input", image_in);
        }
        if (!image_out.empty ()) {
            cv::imshow ("output", image_out);
            cv::moveWindow ("output", image_out.size ().width, 0);
        }
        cv::waitKey (1);
        std::this_thread::sleep_for (std::chrono::milliseconds (1000 / fps));
    }

    double average_duration = total_duration / total_count;
    std::cout << "segmentation on average took " << average_duration << " µs; ("
              << std::round (average_duration / 1000) << " ms)" << std::endl;
    return EXIT_SUCCESS;
}
