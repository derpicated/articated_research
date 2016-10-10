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

cv::Mat vision_methods::segmentation (const cv::Mat& image_in,
std::vector<cv::KeyPoint>& key_points) {
    cv::Mat image_out;

    // blob detection creation
    cv::SimpleBlobDetector::Params blob_detector_params;
    blob_detector_params.filterByArea        = true;
    blob_detector_params.maxArea             = 10000.0;
    blob_detector_params.minArea             = 10.0;
    blob_detector_params.minDistBetweenBlobs = 5.0; // 50?
    cv::SimpleBlobDetector blob_detector (blob_detector_params);

    // segmentation
    cv::Canny (image_in, image_out, 255, 100);
    blob_detector.detect (image_out, key_points);

    return image_out;
}
// blob_detector_params.blobColor;
// blob_detector_params.filterByCircularity;
// blob_detector_params.filterByColor;
// blob_detector_params.filterByConvexity;
// blob_detector_params.filterByInertia;
// blob_detector_params.maxCircularity;
// blob_detector_params.maxConvexity;
// blob_detector_params.maxInertiaRatio;
// blob_detector_params.maxThreshold;
// blob_detector_params.minCircularity;
// blob_detector_params.minConvexity;
// blob_detector_params.minInertiaRatio;
// blob_detector_params.minRepeatability;
// blob_detector_params.minThreshold;
// blob_detector_params.thresholdStep;

/*
Canny{ id: canny, input: blur.output, threshold1 : 255, threshold2 : 100,
visible:true }

StructuringElement{
    id : se
    shape : StructuringElement.MORPH_ELLIPSE
    ksize : "15x15"
}

Dilate{
    input : canny.output
    id: dilate
    kernel : se.output
    iterations : 1
    visible: true
}
// detect blobs
SimpleBlobDetector{
    id : fastFeatureDetector
    input : canny.output
    params : {
        'minDistanceBetweenBlobs': 50.0,
        'minArea' : 10.0,
        'maxArea': 10000.0
    }
    visible: true
}
Threshold{
    id: thres
    input: grey.output
    thresholdType: Threshold.BINARY
    maxVal: 255
    thresh: 170
    visible: true
}
Erode{
    input : thres.output
    kernel : se.output
    iterations : 1
    visible: true
}*/
