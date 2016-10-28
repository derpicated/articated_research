project (segmentation_test)

add_executable(segmentation_test main.cpp)
target_link_libraries(
    segmentation_test
        vision_methods
        ${OpenCV_LIBS}
)
