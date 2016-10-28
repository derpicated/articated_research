#include "vision_methods.hpp"
#include "movement3d.hpp"
#include <opencv2/opencv.hpp>
#include <string>

namespace cv {
// needed for map usage
bool operator< (const KeyPoint& point, const KeyPoint& other_point) {
    bool ans = false;
    if (point.pt.x < other_point.pt.x) {
        ans = true;
    } else if (point.pt.x == other_point.pt.x && point.pt.y < other_point.pt.y) {
        ans = true;
    }
    return ans;
}
bool operator!= (const KeyPoint& point, const KeyPoint& other_point) {
    bool ans = true;
    if (point.pt.x == other_point.pt.x && point.pt.y == other_point.pt.y) {
        ans = false;
    }
    return ans;
}
}

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
    cv::Ptr<cv::SimpleBlobDetector> blob_detector =
    cv::SimpleBlobDetector::create (blob_detector_params);

    // blob detection
    blob_detector->detect (image_in, key_points);

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
    std::map<cv::KeyPoint, std::vector<cv::KeyPoint>> neighbours;

    // get all neighbours for each blob
    for (cv::KeyPoint point : key_points) {
        float range = point.size * _BLOB_SIZE_RATIO;
        float x     = point.pt.x;
        float y     = point.pt.y;

        for (cv::KeyPoint other_point : key_points) {
            if (point != other_point) {
                float dx       = x - other_point.pt.x;
                float dy       = y - other_point.pt.y;
                float distance = sqrt ((dx * dx) + (dy * dy));

                // if other_point is in range, group it with point
                if (distance < range) {
                    neighbours[point].push_back (other_point);
                }
            }
        }
    }

    // recursively link all neighbours into groups
    while (!neighbours.empty ()) {
        std::vector<cv::KeyPoint> potential_marker;
        extract_groups_link (neighbours, potential_marker, neighbours.begin ()->first);
        potential_markers.push_back (potential_marker);
    }
}

void vision_methods::extract_groups_link (
std::map<cv::KeyPoint, std::vector<cv::KeyPoint>>& neighbours,
std::vector<cv::KeyPoint>& potential_marker,
const cv::KeyPoint& point) {
    // if the point hasnt been processed yet
    if (neighbours.find (point) != neighbours.end ()) {
        // add the point to the markert
        // get its neighbours
        // and remove the from the unprocessed lis
        potential_marker.push_back (point);
        std::vector<cv::KeyPoint> neighbour_list = neighbours[point];
        neighbours.erase (point);

        for (cv::KeyPoint neighbour_point : neighbour_list) {
            // link all the neighbours neighbours
            extract_groups_link (neighbours, potential_marker, neighbour_point);
        }
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

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const cv::Mat& image_reference) {
    cv::Mat preprocessed, segmented;
    preprocessed = preprocessing (image_reference);
    segmented    = segmentation (preprocessed);
    std::map<unsigned int, cv::Point2f> marker_points;
    extraction (segmented, marker_points);
    set_reference (marker_points);
    return _reference_markers;
}

std::map<unsigned int, cv::Point2f> vision_methods::set_reference (
const std::map<unsigned int, cv::Point2f>& marker_points) {
    if (marker_points.size () < _minimal_ref_points) {
        throw std::length_error ("too few reference points; found " +
        std::to_string (marker_points.size ()) + " need " +
        std::to_string (_minimal_ref_points));
    }
    _reference_markers = marker_points;
    return _reference_markers;
}

movement3d vision_methods::classification (const cv::Mat& image) {
    movement3d movement;
    cv::Mat preprocessed, segmented;
    preprocessed = preprocessing (image);
    segmented    = segmentation (preprocessed);
    std::map<unsigned int, cv::Point2f> marker_points;
    extraction (segmented, marker_points);
    movement = classification (marker_points);
    return movement;
}

movement3d vision_methods::classification (
const std::map<unsigned int, cv::Point2f>& marker_points) {
    movement3d movement;
    std::vector<cv::Point2f> ref_points, mark_points;
    // convert reference and markers to matching vectors
    for (auto const& marker : _reference_markers) {
        if (marker_points.find (marker.first) != marker_points.end ()) {
            ref_points.push_back (_reference_markers.at (marker.first));
            mark_points.push_back (marker_points.at (marker.first));
        }
    }
    // check size
    if (ref_points.size () < _minimal_ref_points || mark_points.size () < _minimal_ref_points) {
        throw std::length_error (
        "too few match points; found " + std::to_string (ref_points.size ()));
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
