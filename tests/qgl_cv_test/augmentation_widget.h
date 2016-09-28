// gl_testwidget.h

#ifndef AUGMENTATION_WIDGET_H
#define AUGMENTATION_WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <opencv2/opencv.hpp>

QMatrix4x4 m_projection;


class augmentation_widget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
    public:
    augmentation_widget (QWidget* parent = 0);
    ~augmentation_widget ();

    void initializeGL ();
    void resizeGL (int w, int h);
    void paintGL ();

    QSize minimumSizeHint () const;
    QSize sizeHint () const;

    public slots:
    // slots for xyz-rotation slider
    void setXRotation (int angle);
    void setYRotation (int angle);
    void setZRotation (int angle);

    signals:
    // signaling rotation from mouse movement
    void xRotationChanged (int angle);
    void yRotationChanged (int angle);
    void zRotationChanged (int angle);

    private:
    void draw ();

    unsigned int framerate = 30;
    int xRot;
    int yRot;
    int zRot;
    QTimer* frameTimer;
    QPoint lastPos;
    GLuint texture_background;
    cv::VideoCapture cap;
};

#endif // AUGMENTATION_WIDGET_H
