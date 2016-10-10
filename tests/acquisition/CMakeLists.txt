project(acquisition_demo)

find_package(OpenCV REQUIRED)

add_executable(acquisition_demo demo.cpp)
target_link_libraries(
    acquisition_demo
        acquisition
        ${OpenCV_LIBS}
)

project(acquisition_test)
add_executable(acquisition_test test.cpp)
find_package( OpenCV REQUIRED ts)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    acquisition_test
        acquisition
        ${OpenCV_LIBS}
        gtest
        gtest_main
)
add_test( acquisition_test acquisition_test ${SAMPLES_DIR})
