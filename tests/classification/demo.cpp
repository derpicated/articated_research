#include "movement3d.hpp"
#include "vision_methods.hpp"
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif

// source ...
// <http://stackoverflow.com/questions/35942095/opencv-strange-rotation-and-translation-matrices-from-decomposehomographymat>

void print_movement (std::map<unsigned int, cv::Point2f> ref,
std::map<unsigned int, cv::Point2f> match);

int main () {
    std::cout << "classification demo" << std::endl;

    /**
     * x x
     * x x =>
     *        x x
     *        x x
     */
    // clang-format off
    print_movement ({
        { 1, { 0, 0 } }, { 2, { 4, 0 } },
        { 3, { 0, 4 } }, { 4, { 4, 4 } }
    }, {
        { 1, { 0, 4 } }, { 2, { 4, 4 } },
        { 3, { 0, 8 } }, { 4, { 4, 8 } }
    });
    // clang-format on

    /**
     * x x    x x
     *        x x
     * x x =>
     */
    // clang-format off
    print_movement ({
        { 1, { 0, 0 } }, { 2, { 4, 0 } },
        { 3, { 0, 4 } }, { 4, { 4, 4 } }
    }, {
        { 1, { 0.2, 0 } }, { 2, { 3.8, 0 } },
        { 3, { 0, 2 } }, { 4, { 4, 2 } }
    });
    // clang-format on

    return EXIT_SUCCESS;
}

void print_movement (std::map<unsigned int, cv::Point2f> ref,
std::map<unsigned int, cv::Point2f> match) {
    vision_methods test_vm;
    movement3d movement;

    test_vm.set_reference (ref);
    movement = test_vm.classification (match);

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "rot x: " << movement.rot_x () << std::endl;
    std::cout << "rot y: " << movement.rot_y () << std::endl;
    std::cout << "rot z: " << movement.rot_z () << std::endl;
    std::cout << std::endl;

    GLfloat gl[movement3d::GL44_SIZE];
    std::cout << "rot gl x: " << std::endl;
    movement.rot_x_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        std::cout << gl[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "rot gl y: " << std::endl;
    movement.rot_y_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        std::cout << gl[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "rot gl z: " << std::endl;
    movement.rot_z_gl (gl);
    for (unsigned int i = 0; i < movement3d::GL44_SIZE; i++) {
        std::cout << gl[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "translation x: " << movement.trans_x () << std::endl;
    std::cout << "translation y: " << movement.trans_y () << std::endl;
    std::cout << std::endl;

    std::cout << "scale: " << movement.scale () << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}
