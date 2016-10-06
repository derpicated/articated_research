#include "acquisition.hpp"

int main () {
    acquisition acquisition_test;
    // set camera source in range
    // set camera source out of range and catch exception
    acquisition_test.source (acquisition_test.cam_count () - 1);
    try {
        acquisition_test.source (acquisition_test.cam_count ());
    } catch (const std::range_error error) {
        std::cout << "---------- source gave me something!" << std::endl;
    }
    std::cout << "cam count is: " << acquisition_test.cam_count () << std::endl;
    return 0;
}
