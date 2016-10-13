project(augmentation_test)
find_package(Qt5 REQUIRED Core Gui Widgets OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set( augmentation_test_SOURCES   main.cpp window.cpp )
set( augmentation_test_HEADERS   window.h )
set( augmentation_test_FORMS     window.ui )
qt5_wrap_cpp(augmentation_test_MOC ${augmentation_test_HEADERS})
qt5_wrap_ui(augmentation_test_UI_HEADERS ${augmentation_test_FORMS})

add_executable( augmentation_test ${augmentation_test_SOURCES}
                ${augmentation_test_UI_HEADERS}  ${augmentation_test_MOC})
target_link_libraries(augmentation_test augmentation ${QT_LIBRARIES} GL opencv_core opencv_highgui )

qt5_use_modules(augmentation_test Core Gui Widgets OpenGL)
