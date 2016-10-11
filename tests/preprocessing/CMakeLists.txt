project (preprocessing_demo)

find_package(OpenCV REQUIRED)

add_executable(preprocessing_demo demo.cpp)
target_link_libraries(
    preprocessing_demo
        vision_methods
        ${OpenCV_LIBS}
)
