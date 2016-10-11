project (extraction_test)

find_package(OpenCV REQUIRED)
add_executable(extraction_test main.cpp)
target_link_libraries(
    extraction_test
        vision_methods
        ${OpenCV_LIBS}
)
