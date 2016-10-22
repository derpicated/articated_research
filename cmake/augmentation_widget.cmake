find_package(Qt5 REQUIRED Core Gui Widgets OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( augmentation_SOURCES ${SRC_DIR}/augmentation_widget.cpp )
set( augmentation_HEADERS ${INCLUDE_DIR}/augmentation_widget.h)
qt5_wrap_cpp(augmentation_MOC ${augmentation_HEADERS})

add_library( augmentation ${augmentation_SOURCES}  ${augmentation_MOC} )
target_link_libraries( augmentation ${QT_LIBRARIES} GL opencv_core opencv_highgui )
target_include_directories ( augmentation PUBLIC ${INCLUDE_DIR} )

qt5_use_modules( augmentation Core Gui Widgets OpenGL )
