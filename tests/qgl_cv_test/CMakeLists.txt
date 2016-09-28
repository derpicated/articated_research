project(qgl_cv_test)
find_package(Qt5 REQUIRED Core Gui Widgets OpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#-----------------------------------------------------------------------------
set( qgl_cv_test_SOURCES   main.cpp window.cpp augmentation_widget.cpp )
set( qgl_cv_test_HEADERS   window.h augmentation_widget.h)
set( qgl_cv_test_FORMS     window.ui )
#qt5_wrap_cpp( qgl_cv_test_MOC ${qgl_cv_test_HEADERS} )
qt5_wrap_ui(qgl_cv_test_UI_HEADERS ${qgl_cv_test_FORMS})
#${qgl_cv_test_MOC}
add_executable( qgl_cv_test ${qgl_cv_test_SOURCES}
                ${qgl_cv_test_UI_HEADERS})

target_link_libraries(qgl_cv_test ${QT_LIBRARIES} GL opencv_core opencv_highgui)
#target_link_libraries(helloworld Qt5::Widgets)

qt5_use_modules(qgl_cv_test Core Gui Widgets OpenGL)

#message(warning ${qgl_cv_test_UI_HEADERS})
#-----------------------------------------------------------------------------
