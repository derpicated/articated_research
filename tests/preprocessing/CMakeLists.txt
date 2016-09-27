project (preprocessing_test)

find_package( OpenCV REQUIRED )
add_executable(preprocessing_test main.cpp)
target_link_libraries(preprocessing_test vision_methods)
target_link_libraries( preprocessing_test ${OpenCV_LIBS} )
