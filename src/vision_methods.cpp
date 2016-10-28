#include "vision_methods.hpp"
#include "movement3d.hpp"
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
    return image_in;
}

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const cv::Mat& image_reference) {
    (void)image_reference;
    throw std::runtime_error (
    "missing implementation of set_reference from image");
    return {};
}

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const std::map<unsigned int, cv::Point2f>& markers) {
    if (markers.size () < _minimal_ref_points) {
        throw std::length_error ("too few reference points");
    }
    _reference_markers = markers;
    return _reference_markers;
}

movement3d vision_methods::classification (const cv::Mat& image) {
    (void)image;
    movement3d empty_tmp;
    // run image through:
    // - preprocessing
    // - segmentation
    // - extraction
    // - classification
    // and return the movement
    return empty_tmp;
}

movement3d vision_methods::classification (const std::map<unsigned int, cv::Point2f>& markers) {
    movement3d movement;
    std::vector<cv::Point2f> ref_points, mark_points;
    // convert reference and markers to matching vectors
    for (auto const& marker : _reference_markers) {
        if (markers.find (marker.first) != markers.end ()) {
            ref_points.push_back (_reference_markers.at (marker.first));
            mark_points.push_back (markers.at (marker.first));
        }
    }

    // find homography between points
    cv::Mat H = cv::findHomography (ref_points, mark_points);

    // decompose and find information that is in the transformation matrix
    std::vector<cv::Mat> rotations, translations, normals;
    cv::decomposeHomographyMat (H, _K, rotations, translations, cv::noArray ());

    // convert to floats
    H.convertTo (H, CV_32F);
    for (auto rotation : rotations) {
        rotation.convertTo (rotation, CV_32F);
    }
    for (auto translation : translations) {
        translation.convertTo (translation, CV_32F);
    }
    for (auto normal : normals) {
        normal.convertTo (normal, CV_32F);
    }

    // set x, y, z if available
    // clang-format off
    float default_rot_val[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    // clang-format on
    cv::Mat default_rot_mat = cv::Mat (3, 3, CV_32F, default_rot_val);
    // x
    if (rotations.size () >= 1) {
        movement.rot_x (rotations[0]);
    } else {
        movement.rot_x (default_rot_mat);
    }
    // y
    if (rotations.size () >= 2) {
        movement.rot_y (rotations[1]);
    } else {
        movement.rot_y (default_rot_mat);
    }
    // z
    if (rotations.size () >= 1) {
        movement.rot_z (rotations[2]);
    } else {
        movement.rot_z (default_rot_mat);
    }

    // set translation
    //    a b c  c: Tx
    // H: d e f  f: Ty
    //    0 0 1
    // x:
    movement.trans_x (H.at<float> (cv::Point (2, 0)));
    // y:
    movement.trans_y (H.at<float> (cv::Point (2, 1)));

    // set scale
    movement.scale (1); // for now
    return movement;
}
