project(articated_app)
find_package(Qt5 REQUIRED Core Gui Widgets Multimedia OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set( articated_SOURCES   ${SRC_DIR}/main.cpp ${SRC_DIR}/window.cpp )
set( articated_HEADERS   ${INCLUDE_DIR}/window.h )
qt5_wrap_cpp(articated_MOC ${articated_HEADERS})


add_executable( articated_app ${articated_SOURCES} ${articated_MOC})
add_definitions(-DSAMPLES_DIR="${SAMPLES_DIR}")
target_link_libraries(
    articated_app
${QT_LIBRARIES} GL opencv_core opencv_highgui
        acquisition
        vision_methods
        augmentation
)

qt5_use_modules(articated_app Core Gui Widgets Multimedia OpenGL)
