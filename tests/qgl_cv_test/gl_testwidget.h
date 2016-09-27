// gl_testwidget.h

#ifndef GL_TestWidget_H
#define GL_TestWidget_H

#include <QGLWidget>
#include <opencv2/opencv.hpp>

class GL_TestWidget : public QGLWidget {
    Q_OBJECT
    public:
    explicit GL_TestWidget (QWidget* parent = 0);
    ~GL_TestWidget ();
    signals:

    public slots:

    protected:
    void initializeGL ();
    void paintGL ();
    void resizeGL (int width, int height);

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

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
    GLuint texture_background;
    cv::VideoCapture cap;
};

#endif // GL_TestWidget_H
