project(acquisition_demo)

add_executable(acquisition_demo demo.cpp)
target_link_libraries(
    acquisition_demo
        acquisition
        ${OpenCV_LIBS}
)

project(acquisition_test)
add_executable(acquisition_test test.cpp)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    acquisition_test
        acquisition
        ${OpenCV_LIBS}
        gtest
        gtest_main
)
add_test(NAME acquisition_test
         COMMAND acquisition_test
         WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
