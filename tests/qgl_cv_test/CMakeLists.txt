CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(qgl_cv_test)
FIND_PACKAGE(Qt4 REQUIRED)
SET( QT_USE_QTOPENGL TRUE )
set (CMAKE_PREFIX_PATH )
INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} "/usr/include/qt4")
#-----------------------------------------------------------------------------


SET( qgl_cv_test_SOURCES   main.cpp window.cpp gl_testwidget.cpp )
SET( qgl_cv_test_HEADERS   window.h gl_testwidget.h)
SET( qgl_cv_test_FORMS     window.ui )

QT4_WRAP_CPP( qgl_cv_test_MOC ${qgl_cv_test_HEADERS} )
QT4_WRAP_UI( qgl_cv_test_UI_HEADERS ${qgl_cv_test_FORMS} )

ADD_EXECUTABLE(
    qgl_cv_test
    ${qgl_cv_test_SOURCES}
    ${qgl_cv_test_MOC}
    ${qgl_cv_test_UI_HEADERS}
)

TARGET_LINK_LIBRARIES(qgl_cv_test ${QT_LIBRARIES} QtOpenGL GL opencv_core opencv_highgui)
#-----------------------------------------------------------------------------
