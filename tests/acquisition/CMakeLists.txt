project(acquisition_demo)

find_package(OpenCV REQUIRED)
add_executable(acquisition_demo demo.cpp)
target_link_libraries(
    acquisition_demo
        acquisition
        ${OpenCV_LIBS}
)
