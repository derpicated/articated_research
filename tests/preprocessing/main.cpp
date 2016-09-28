#include "vision_methods.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
/**
 * Test the vision method preprocessing
 */
int main (int argc, char const* argv[]) {
    // argv 1: type
    // argv 2: data
    if (argc != 3) {
        std::cout << "Usage: preprocessing_test date_type date" << std::endl;
        std::cout << "data_type: v = video" << std::endl;
        std::cout << "data_type: i = image" << std::endl;
        std::cout << "data_type: c = camera (file is cam ID)" << std::endl;
        exit (EXIT_FAILURE);
    }
    cv::Mat image_in, image_out;
    vision_methods preprocessing_test;
    std::string file = argv[2];
    cv::VideoCapture cap;
    cv::namedWindow ("input", cv::WINDOW_AUTOSIZE);
    const int fps = 30;
    std::clock_t start_time;
    bool loop = true;
    switch ((*argv[1])) {
        case 'c':
            if (!cap.open (std::stoi (file))) {
                std::cout << "camera could not be opened" << std::endl;
                exit (EXIT_FAILURE);
            }
        case 'v':
            if (!cap.open ((file))) {
                std::cout << "video could not be opened" << std::endl;
                exit (EXIT_FAILURE);
            }
    }

    while (loop) {
        start_time = std::clock ();
        switch ((*argv[1])) {
            case 'i':
                image_in = cv::imread (file, CV_LOAD_IMAGE_COLOR);

                if (!image_in.data) {
                    std::cout << "could not open or find the image" << std::endl;
                    exit (EXIT_FAILURE);
                }
                loop = false;
                break;
            case 'c': cap >> image_in; break;
            case 'v': cap >> image_in; break;
            default:
                std::cout << "not suported" << std::endl;
                exit (EXIT_FAILURE);
        }
        image_out = preprocessing_test.preprocessing (image_in);
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
