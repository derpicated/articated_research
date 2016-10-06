#ifndef ACQUISITION_HPP
#define ACQUISITION_HPP

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class acquisition {
    private:
    /* data */
    const bool type_camera = true;
    const bool type_file   = false;
    bool type              = type_camera;
    std::string _file      = "";
    int _device            = -1;

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
    acquisition (const int device = 0);
    acquisition (const std::string& filename);
    ~acquisition ();
    void source (const int device = 0);
    void source (const std::string& filename);
    cv::Mat capture ();

    int cam_count ();
};

#endif // ACQUISITION_HPP
