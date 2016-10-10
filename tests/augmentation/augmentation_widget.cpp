// augmentation_widget.cpp

#include <QDebug>

#include "augmentation_widget.h"

augmentation_widget::augmentation_widget (QWidget* parent)
: QOpenGLWidget (parent)
, _cap (0)
, _scale_factor (1.0f)
, _x_pos (0.0f)
, _y_pos (0.0f)
, _x_rot (0)
, _y_rot (0)
, _z_rot (0)
, _frame_timer (new QTimer (this)) {
    connect (_frame_timer, SIGNAL (timeout ()), this, SLOT (update ()));
    _frame_timer->setInterval (1000 / _framerate);
    _frame_timer->start ();
}

augmentation_widget::~augmentation_widget () {
    delete _frame_timer;
}

QSize augmentation_widget::minimumSizeHint () const {
    return QSize (100, 100);
}

QSize augmentation_widget::sizeHint () const {
    return QSize (500, 500);
}

static void qNormalizeAngle (int& angle) {
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
}

void augmentation_widget::setScale (float scale) {
    _scale_factor = scale;
    // emit xPositionChanged (location);
}

void augmentation_widget::setXPosition (float location) {
    _x_pos = location;
    // emit xPositionChanged (location);
}

void augmentation_widget::setYPosition (float location) {
    _y_pos = location;
    // emit yPositionChanged (location);
}

void augmentation_widget::setXRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != _x_rot) {
        _x_rot = angle;
        emit xRotationChanged (angle);
    }
}

void augmentation_widget::setYRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != _y_rot) {
        _y_rot = angle;
        emit yRotationChanged (angle);
    }
}

void augmentation_widget::setZRotation (int angle) {
    qNormalizeAngle (angle);
    if (angle != _z_rot) {
        _z_rot = angle;
        emit zRotationChanged (angle);
    }
}

void augmentation_widget::initializeGL () {
    initializeOpenGLFunctions ();

    glClearColor (0, 0, 0, 1.0f);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glMatrixMode (GL_PROJECTION);
    glEnable (GL_TEXTURE_2D);
    glGenTextures (1, &_texture_background);

    // glMatrixMode (GL_MODELVIEW);
    /*static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
    glLoadIdentity ();
    gluPerspective (33.7, 1.3, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW)*/
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

void augmentation_widget::paintGL () {
    QOpenGLFunctions* f = QOpenGLContext::currentContext ()->functions ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    cv::Mat frame;
    _cap >> frame;
    if (frame.empty ()) {
        printf ("empty video frame"); // TODO throw error here
        return;
    }
    // create background texture
    glBindTexture (GL_TEXTURE_2D, _texture_background);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR,
    GL_UNSIGNED_BYTE, frame.ptr ());

    // glMatrixMode (GL_MODELVIEW);

    // draw background
    glTranslatef (0.0, 0.0, -10.0);

    glBegin (GL_QUADS);
    glTexCoord2f (0.0, 1.0);
    glVertex3f (-4.0, -3.0, -1.0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f (4.0, -3.0, -1.0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f (4.0, 3.0, -1.0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (-4.0, 3.0, -1.0);
    glEnd ();
    // glPopMatrix ();

    glPushMatrix ();
    glScalef (_scale_factor, _scale_factor, _scale_factor);
    glTranslatef (_x_pos, _y_pos, 0);
    glRotatef (_x_rot, 1, 0, 0);
    glRotatef (_y_rot, 0, 1, 0);
    glRotatef (_z_rot, 0, 0, 1);

    glBegin (GL_QUADS);
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
    glPopMatrix ();
}
