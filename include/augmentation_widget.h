// gl_testwidget.h

#ifndef AUGMENTATION_WIDGET_H
#define AUGMENTATION_WIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

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
    void setScale (float factor);
    void setXPosition (float location);
    void setYPosition (float location);
    void setZRotation (int angle);
    void setXRotation (int angle);
    void setYRotation (int angle);

    signals:
    // signaling rotation from mouse movement
    void xRotationChanged (int angle);
    void yRotationChanged (int angle);
    void zRotationChanged (int angle);

    private:
    const unsigned int _framerate = 30;
    float _scale_factor;
    float _x_pos;
    float _y_pos;
    int _x_rot;
    int _y_rot;
    int _z_rot;
    cv::VideoCapture _cap;
    GLuint _texture_background;
    QTimer* _frame_timer;
};

#endif // AUGMENTATION_WIDGET_H
