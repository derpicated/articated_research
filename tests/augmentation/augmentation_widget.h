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
    void setXPosition (int location);
    void setYPosition (int location);
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
    float _x_pos;
    float _y_pos;
    int _x_rot;
    int _y_rot;
    int _z_rot;
    QTimer* _frame_timer;
    QPoint _lastPos;
    GLuint _texture_background;
    cv::VideoCapture _cap;
};

#endif // AUGMENTATION_WIDGET_H
