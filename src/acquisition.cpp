#include "acquisition.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <unistd.h>

acquisition::acquisition (const int device)
: type (type_camera) {
    source (device);
}

acquisition::acquisition (const std::string& filename)
: type (type_camera) {
    source (filename);
}

acquisition::~acquisition () {
}

void acquisition::source (const int device) {
    if (!(device < cam_count ())) {
        throw std::range_error ("camera ID not available");
    }
    _device = device;
}

void acquisition::source (const std::string& filename) {
    _file = filename;
}

cv::Mat acquisition::capture () {
    cv::Mat image;
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
    cv::redirectError (handleError); // redirect opencv errors
    cv::VideoCapture cam;
    int max   = 10; // max to test
    int count = 0;
    for (count = 0; count < max; count++) {
        cv::redirectError (handleError);
        try {
            cam.open (count);
        } catch (...) {
            break;
        }
    }
    cv::redirectError (nullptr); // set back to default
    return count;
}
