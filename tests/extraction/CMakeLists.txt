project (extraction_test)

add_executable(extraction_test main.cpp)
target_link_libraries(
    extraction_test
        vision_methods
        ${OpenCV_LIBS}
)
