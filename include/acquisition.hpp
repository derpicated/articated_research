#ifndef ACQUISITION_HPP
#define ACQUISITION_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class acquisition {
    private:
    cv::VideoCapture _capture;

    /**
     * handle opencv errors
     * @param  status    error code (CV::Error::Code)
     * @param  func_name function name
     * @param  err_msg   error description
     * @param  file_name source file name
     * @param  line      line number in the source file
     * @param  userdata  [description]
     * @return           [description]
     */
    static int handleError (int status,
    const char* func_name,
    const char* err_msg,
    const char* file_name,
    int line,
    void* userdata);

    public:
    acquisition ();
    acquisition (const int device);
    acquisition (const std::string& filename);
    ~acquisition ();

    /**
     * set source of capture data
     * @param device is the camera identifier
     */
    void source (const int device = -1);

    /**
     * set source of capture data
     * @param filename the to be captured file
     */
    void source (const std::string& filename);

    /**
     * capture data
     * @return return a captured frame
     */
    cv::Mat capture ();

    /**
     * get camera count
     * This moment this will just return the max check value
     * (10). This is because opencv is not working correctly.
     * @return number of cameras connected
     */
    int cam_count ();
};

#endif // ACQUISITION_HPP
