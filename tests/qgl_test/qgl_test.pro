QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qgl_test
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
        gl_testwidget.cpp

HEADERS  += window.h \
        gl_testwidget.h

FORMS    += window.ui
