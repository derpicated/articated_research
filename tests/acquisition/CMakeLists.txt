project(acquisition_test)

find_package(OpenCV REQUIRED)
add_executable(acquisition_test main.cpp)
target_link_libraries(
    acquisition_test
        acquisition
        ${OpenCV_LIBS}
)
