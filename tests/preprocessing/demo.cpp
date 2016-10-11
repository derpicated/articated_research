#include "vision_methods.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
/**
 * Test the vision method preprocessing
 */
int main (int argc, char const* argv[]) {
    // argv 1: type
    // argv 2: data
    if (argc != 3) {
        std::cout << "Usage: preprocessing_demo date_type date" << std::endl;
        std::cout << "data_type: v = video" << std::endl;
        std::cout << "data_type: i = image" << std::endl;
        std::cout << "data_type: c = camera (file is cam ID)" << std::endl;
        exit (EXIT_FAILURE);
    }
    cv::Mat image_in, image_out;
    vision_methods preprocessing_test;
    cv::VideoCapture cap;
    // std::clock_t start_time;
    std::chrono::high_resolution_clock::time_point start_time;
    bool loop              = true;
    const std::string type = argv[1];
    const std::string file = argv[2];
    const int fps          = 30;
    // open the file
    if (type == "c") {
        if (!cap.open (std::stoi (file))) {
            std::cout << "camera could not be opened" << std::endl;
            exit (EXIT_FAILURE);
        }
    } else if (type == "v") {
        if (!cap.open ((file))) {
            std::cout << "video could not be opened" << std::endl;
            exit (EXIT_FAILURE);
        }
    }
    // loop if necessary
    while (loop) {
        if (type == "i") {
            image_in = cv::imread (file, CV_LOAD_IMAGE_COLOR);

            if (!image_in.data) {
                std::cout << "could not open or find the image" << std::endl;
                exit (EXIT_FAILURE);
            }
            loop = false;
        } else if (type == "c") {
            cap >> image_in;
        } else if (type == "v") {
            cap >> image_in;
        } else {
            std::cout << "not suported" << std::endl;
            exit (EXIT_FAILURE);
        }
        start_time    = std::chrono::high_resolution_clock::now ();
        image_out     = preprocessing_test.preprocessing (image_in);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds> (
        std::chrono::high_resolution_clock::now () -
        start_time).count ();

        std::cout << "preprocessing took " << duration << " µs; ("
                  << duration / 1000 << " ms )" << std::endl;
        if (!image_in.empty ()) {
            cv::imshow ("input", image_in);
        }
        if (!image_in.empty ()) {
            cv::imshow ("output", image_out);
            cv::moveWindow ("output", image_out.size ().width, 0);
        }
        cv::waitKey (1);
        std::this_thread::sleep_for (
        std::chrono::milliseconds (int(float(1000 * (1 / fps)))));
    }
    cv::waitKey (0);
    return EXIT_SUCCESS;
}
