// gl_testwidget.h

#ifndef AUGMENTATION_WIDGET_H
#define AUGMENTATION_WIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <opencv2/opencv.hpp>

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
    void setXRotation (int angle);
    void setYRotation (int angle);
    void setZRotation (int angle);

    signals:
    // signaling rotation from mouse movement
    void xRotationChanged (int angle);
    void yRotationChanged (int angle);
    void zRotationChanged (int angle);

    private:
    unsigned int _framerate = 30;
    int _xRot;
    int _yRot;
    int _zRot;
    QTimer* _frame_timer;
    QPoint _lastPos;
    GLuint _texture_background;
    cv::VideoCapture _cap;
};

#endif // AUGMENTATION_WIDGET_H
