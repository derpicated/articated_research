project(classification_demo)

add_executable(classification_demo demo.cpp)
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    classification_demo
        vision_methods
        movement3d
        ${OpenCV_LIBS}
)

project(classification_test)
add_executable(classification_test test.cpp)
target_link_libraries(
    classification_test
        vision_methods
        movement3d
        ${OpenCV_LIBS}
)
add_test(NAME classification_test
         COMMAND classification_test
         WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
