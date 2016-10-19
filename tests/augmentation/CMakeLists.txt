project(augmentation_test)
find_package(Qt5 REQUIRED Core Gui Widgets OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#-----------------------------------------------------------------------------
set( augmentation_test_SOURCES   main.cpp window.cpp augmentation_widget.cpp )
set( augmentation_test_HEADERS   window.h augmentation_widget.h)
set( augmentation_test_FORMS     window.ui )
qt5_wrap_ui(augmentation_test_UI_HEADERS ${augmentation_test_FORMS})

add_executable( augmentation_test ${augmentation_test_SOURCES}
                ${augmentation_test_UI_HEADERS})

target_link_libraries(augmentation_test ${QT_LIBRARIES} GL opencv_core opencv_highgui opencv_videoio)

qt5_use_modules(augmentation_test Core Gui Widgets OpenGL)
#-----------------------------------------------------------------------------
