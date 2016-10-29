#include "movement3d_filter.hpp"
#include "movement3d.hpp"

movement3d_average::movement3d_average (unsigned int samples)
: _samples (samples) {
}

movement3d_average::~movement3d_average () {
}

movement3d movement3d_average::average () {
    movement3d empty;
    return empty;
}

movement3d movement3d_average::average (movement3d movement) {
    return movement;
}
