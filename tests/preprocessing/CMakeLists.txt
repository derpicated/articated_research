project (preprocessing_demo)

find_package(OpenCV REQUIRED)

add_executable(preprocessing_demo demo.cpp)
target_link_libraries(
    preprocessing_demo
        vision_methods
        ${OpenCV_LIBS}
)

project(preprocessing_test)
add_executable(preprocessing_test test.cpp)
find_package( OpenCV REQUIRED ts)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    preprocessing_test
        acquisition
        vision_methods
        ${OpenCV_LIBS}
        gtest
        gtest_main
)
add_test( preprocessing_test preprocessing_test)
