project(acquisition_demo)

find_package(OpenCV REQUIRED)

add_executable(acquisition_demo demo.cpp)
target_link_libraries(
    acquisition_demo
        acquisition
        ${OpenCV_LIBS}
)

project(acquisition_test)
add_executable(acquisition_test test.cpp)
target_link_libraries(
    acquisition_test
        gtest
        gtest_main
)
add_test( acquisition_test acquisition_test )
