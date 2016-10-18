#include "vision_methods.hpp"
//#include <oepncv2/features2d.hpp>
#include <opencv2/opencv.hpp>

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

    // blob detection creation
    cv::SimpleBlobDetector::Params blob_detector_params;
    blob_detector_params.filterByArea = true;
    blob_detector_params.maxArea      = 10000.0;
    blob_detector_params.minArea      = 10.0;
    cv::SimpleBlobDetector blob_detector (blob_detector_params);

    blob_detector.detect (image_in, key_points);

    for (cv::KeyPoint point : key_points) {
        circle (image_out, point.pt, point.size * 2, cv::Scalar (255), -1);
    }
    cv::drawKeypoints (image_out, key_points, image_out);

    extract_markers (key_points, markers);
    return image_out;
}

void vision_methods::extract_markers (std::vector<cv::KeyPoint>& key_points,
std::map<unsigned int, cv::Point2f>& markers) {
    std::vector<std::vector<cv::KeyPoint>> potential_markers;

    while (!key_points.empty ()) {
        cv::KeyPoint key_point = key_points.back ();
        key_points.pop_back ();
        int x = key_point.pt.x;
        int y = key_point.pt.y;
    }

    for (std::vector<cv::KeyPoint> marker_points : potential_markers) {
        unsigned int marker_id = marker_points.size ();
        if (marker_id > 1) {
            cv::Point2f marker_pos;
            markers[marker_id] = marker_pos;
        }
    }
}

/*    std::vector<cv::Vec4i> hierarchy;
    cv::RNG rng;
    cv::findContours (image_in, contours, hierarchy, CV_RETR_TREE,
 CV_CHAIN_APPROX_SIMPLE);

  cv::Mat drawing = cv::Mat::zeros (image_in.size (), CV_8UC3);
  for (unsigned int i = 0; i < contours.size (); i++) {
      cv::Scalar color =
      cv::Scalar (rng.uniform (0, 255), rng.uniform (0, 255), rng.uniform
 (0, 255));
      cv::drawContours (drawing, contours, i, color, 2, 8, hierarchy, 0);
  }

  return drawing;*/

/*
  // blob detection creation
    cv::SimpleBlobDetector::Params blob_detector_params;
    blob_detector_params.filterByArea        = true;
    blob_detector_params.maxArea             = 10000.0;
    blob_detector_params.minArea             = 10.0;
    blob_detector_params.minDistBetweenBlobs = 5.0; // 50?
    cv::SimpleBlobDetector blob_detector (blob_detector_params);

    blob_detector.detect (image_in, key_points);

    int i = 0;
    for (cv::KeyPoint point : key_points) {
        markers[i] = point;
        ++i;
    }

    cv::drawKeypoints (image_in, key_points, image_out);
*/
