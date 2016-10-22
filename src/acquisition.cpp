#include "acquisition.hpp"
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <sstream>
#include <unistd.h>

acquisition::acquisition () {
}

acquisition::acquisition (const int device) {
    source (device);
}

acquisition::acquisition (const std::string& filename) {
    source (filename);
}

acquisition::~acquisition () {
}

void acquisition::source (const int device) {
    if (!(device < cam_count ())) {
        throw std::range_error ("camera ID not available");
    } else if (!(_capture.open (device))) {
        throw std::ifstream::failure ("camera could not be opened");
    }
}

void acquisition::source (const std::string& filename) {
    if (!(_capture.open (filename))) {
        throw std::ifstream::failure ("file could not be opened");
    }
}

cv::Mat acquisition::capture () {
    if (!(_capture.isOpened ())) {
        throw std::runtime_error ("no open capture file/device");
    }
    cv::Mat image;
    _capture >> image;
    return image;
}

int acquisition::handleError (int status,
const char* func_name,
const char* err_msg,
const char* file_name,
int line,
void* userdata) {
    (void)status;
    (void)func_name;
    (void)err_msg;
    (void)file_name;
    (void)line;
    (void)userdata;
    // Do nothing -- will suppress console output
    return 0; // Return value is not used
}
int acquisition::cam_count () {
    // cv::redirectError (handleError); // redirect opencv errors
    cv::VideoCapture cam;
    int max = 10; // max to test
    return max;   // stub implementation
    int count = 0;
    cv::redirectError (handleError);
    for (count = 0; count < max; count++) {
        try {
            cam.open (count);
        } catch (...) {
            break;
        }
    }
    cv::redirectError (nullptr); // set back to default
    return count;
}
