#include "vision_methods.hpp"
//#include <oepncv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>

vision_methods::vision_methods () {
}

vision_methods::~vision_methods () {
}

cv::Mat vision_methods::preprocessing (const cv::Mat& image_in) {
    cv::Mat image_out;
    cvtColor (image_in, image_out, CV_BGR2GRAY);
    cv::GaussianBlur (image_out, image_out, cv::Size (_ksize_x, _ksize_y), _sigma_x, _sigma_y);
    return image_out;
}

cv::Mat vision_methods::segmentation (const cv::Mat& image_in) {
    cv::Mat image_out;

    cv::threshold (image_in, image_out, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    return image_out;
}

cv::Mat vision_methods::extraction (const cv::Mat& image_in,
std::map<unsigned int, cv::Point2f>& markers) {
    std::vector<cv::KeyPoint> key_points;
    cv::Mat image_out (image_in.rows, image_in.cols, CV_8UC1, cv::Scalar (0));

    // blob detector creation
    cv::SimpleBlobDetector::Params blob_detector_params;
    blob_detector_params.filterByArea = true;
    blob_detector_params.maxArea      = 10000.0;
    blob_detector_params.minArea      = 10.0;
    cv::SimpleBlobDetector blob_detector (blob_detector_params);

    // blob detection
    blob_detector.detect (image_in, key_points);

    // marker extraction
    std::vector<std::vector<cv::KeyPoint>> potential_markers;
    extract_groups (key_points, potential_markers);
    extract_markers (potential_markers, markers);

    // debug image construction
    for (cv::KeyPoint point : key_points) {
        circle (image_out, point.pt, point.size * 2, cv::Scalar (255), -1);
    }
    for (auto marker : markers) {
        putText (image_out, std::to_string (marker.first), marker.second,
        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar (0));
    }
    return image_out;
}

void vision_methods::extract_groups (std::vector<cv::KeyPoint> key_points,
std::vector<std::vector<cv::KeyPoint>>& potential_markers) {
    // group keypoints into markers by proximity
    while (!key_points.empty ()) {
        std::vector<cv::KeyPoint> grouped_points;
        cv::KeyPoint key_point = key_points.back ();
        key_points.pop_back ();
        float x = key_point.pt.x;
        float y = key_point.pt.y;

        // check distance against all other key points
        for (auto itr = key_points.begin (); itr != key_points.end ();) {
            float dx       = x - itr->pt.x;
            float dy       = y - itr->pt.y;
            float distance = sqrt ((dx * dx) + (dy * dy));

            // if the point is in range, group it with current point
            if (distance < (key_point.size * _BLOB_SIZE_RATIO)) {
                grouped_points.push_back (*itr);
                key_points.erase (itr);
            } else {
                itr++;
            }
        }

        grouped_points.push_back (key_point);
        potential_markers.push_back (grouped_points);
    }
}

void vision_methods::extract_markers (std::vector<std::vector<cv::KeyPoint>>& potential_markers,
std::map<unsigned int, cv::Point2f>& markers) {
    // calculate marker properties (id, size, location)
    for (std::vector<cv::KeyPoint> marker_points : potential_markers) {
        const unsigned int marker_id = marker_points.size ();

        if (_MIN_MARKER_ID <= marker_id && marker_id <= _MAX_MARKER_ID) {
            cv::Point2f marker_pos;
            float average_x = 0;
            float average_y = 0;

            for (cv::KeyPoint key_point : marker_points) {
                //    average_size += key_point.size;
                average_x += key_point.pt.x;
                average_y += key_point.pt.y;
            }

            // average_size /= marker_id;
            marker_pos.x       = average_x / marker_id;
            marker_pos.y       = average_y / marker_id;
            markers[marker_id] = marker_pos;
        }
    }
}
