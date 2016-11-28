project(articated_android_app)
find_package(Qt5 REQUIRED Core Gui Widgets Multimedia OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set( articated_android_SOURCES   ${SRC_DIR}/main.cpp ${SRC_DIR}/window.cpp )
set( articated_android_HEADERS   ${INCLUDE_DIR}/window.h )
qt5_wrap_cpp(articated_android_MOC ${articated_android_HEADERS})


add_executable( articated_android_app ${articated_android_SOURCES} ${articated_android_MOC})
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    articated_android_app
        ${QT_LIBRARIES}
        GL
        opencv_core
        opencv_highgui
        movement3d
        movement3d_filter
        vision_methods
        acquisition
        vision_methods
        augmentation
)

qt5_use_modules(articated_android_app Core Gui Widgets Multimedia OpenGL)
