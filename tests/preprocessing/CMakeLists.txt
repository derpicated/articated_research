project (preprocessing_demo)

add_executable(preprocessing_demo demo.cpp)
target_link_libraries(
    preprocessing_demo
        vision_methods
        ${OpenCV_LIBS}
)

project(preprocessing_test)
add_executable(preprocessing_test test.cpp)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    preprocessing_test
        acquisition
        vision_methods
        ${OpenCV_LIBS}
)
add_test(NAME preprocessing_test
         COMMAND preprocessing_test
         WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
