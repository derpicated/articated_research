// augmentation_widget.cpp

#include <QDebug>
#include <QtOpenGL>

#include "augmentation_widget.h"

augmentation_widget::augmentation_widget (QWidget* parent)
: QOpenGLWidget (parent)
, cap (0)
, xRot (0)
, yRot (0)
, zRot (0)
, frameTimer (new QTimer (this)) {
    connect (frameTimer, SIGNAL (timeout ()), this, SLOT (update ()));
    frameTimer->setInterval (1 / framerate);
    frameTimer->start ();
}

augmentation_widget::~augmentation_widget () {
    delete frameTimer;
}

QSize augmentation_widget::minimumSizeHint () const {
    return QSize (50, 50);
}

QSize augmentation_widget::sizeHint () const {
    return QSize (400, 400);
}

static void qNormalizeAngle (int& angle) {
    while (angle < 0) angle += 360 * 16;
    while (angle > 360) angle -= 360 * 16;
}

void augmentation_widget::update () {
    paintGL ();
}

void augmentation_widget::setXRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged (angle);
    }
}

void augmentation_widget::setYRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged (angle);
    }
}

void augmentation_widget::setZRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged (angle);
    }
}

void augmentation_widget::initializeGL () {
    initializeOpenGLFunctions ();

    glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glMatrixMode (GL_PROJECTION);
    glEnable (GL_TEXTURE_2D);
    glGenTextures (1, &texture_background);

    /*static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
    glLoadIdentity ();
    gluPerspective (33.7, 1.3, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW)*/
}

void augmentation_widget::paintGL () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glTranslatef (0.0, 0.0, -10.0);
    glRotatef (xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef (yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef (zRot / 16.0, 0.0, 0.0, 1.0);
    draw ();
}

void augmentation_widget::resizeGL (int width, int height) {
    int side = qMin (width, height);
    glViewport ((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
#ifdef QT_OPENGL_ES_1
    glOrthof (-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho (-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode (GL_MODELVIEW);
}

void augmentation_widget::draw () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    cv::Mat frame;
    // acquire frame
    cap >> frame;
    // frame = cv::imread ("../image.jpg", CV_LOAD_IMAGE_COLOR);
    if (frame.empty ()) {
        qDebug () << "empty video frame"; // TODO throw error here
        return;
    }
    // create background texture
    glBindTexture (GL_TEXTURE_2D, texture_background);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR,
    GL_UNSIGNED_BYTE, frame.ptr ());

    // draw background
    glBindTexture (GL_TEXTURE_2D, texture_background);
    // glPushMatrix ();
    glTranslatef (0.0, 0.0, -10.0);

    glBegin (GL_QUADS);
    glTexCoord2f (0.0, 1.0);
    glVertex3f (-4.0, -3.0, 0.0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f (4.0, -3.0, 0.0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f (4.0, 3.0, 0.0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (-4.0, 3.0, 0.0);
    glEnd ();

    // glPopMatrix ();

    // draw triangle
    glBegin (GL_QUADS);
    // qglColor (Qt::red);
    glNormal3f (0, 0, -1);
    glVertex3f (-1, -1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (1, -1, 0);
    glEnd ();

    glBegin (GL_TRIANGLES);
    glNormal3f (0, -1, 0.707);
    glVertex3f (-1, -1, 0);
    glVertex3f (1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glNormal3f (1, 0, 0.707);
    glVertex3f (1, -1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glNormal3f (0, 1, 0.707);
    glVertex3f (1, 1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glNormal3f (-1, 0, 0.707);
    glVertex3f (-1, 1, 0);
    glVertex3f (-1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
}
