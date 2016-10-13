project(classification_demo)

add_executable(classification_demo demo.cpp)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    classification_demo
        vision_methods
        ${OpenCV_LIBS}
)

project(classification_test)
add_executable(classification_test test.cpp)
target_link_libraries(
    classification_test
        vision_methods
        ${OpenCV_LIBS}
        gtest
        gtest_main
)
add_test( classification_test classification_test)
