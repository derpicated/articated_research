// augmentation_widget.cpp

#include "augmentation_widget.h"
#include <GL/gl.h>
#include <QDebug>

augmentation_widget::augmentation_widget (QWidget* parent)
: QOpenGLWidget (parent)
, _scale_factor (1.0f)
, _x_pos (0.0f)
, _y_pos (0.0f)
, _x_rot (0)
, _y_rot (0)
, _z_rot (0)
, _cap (0)
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
    _x_rot = angle;
}

void augmentation_widget::setYRotation (int angle) {
    qNormalizeAngle (angle);
    _y_rot = angle;
}

void augmentation_widget::setZRotation (int angle) {
    qNormalizeAngle (angle);
    _z_rot = angle;
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
    glEnable (GL_COLOR_MATERIAL);

    glMatrixMode (GL_MODELVIEW);
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
    glLoadIdentity ();
    // gluPerspective (33.7, 1.3, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
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
    glMatrixMode (GL_MODELVIEW);
    // QOpenGLFunctions* f = QOpenGLContext::currentContext ()->functions ();
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


    // draw background
    glTranslatef (0.0, 0.0, -10.0);

    glBegin (GL_QUADS);
    glColor3f (1, 1, 1);
    glTexCoord2f (0.0, 1.0);
    glVertex3f (-4.0, -3.0, -2.0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f (4.0, -3.0, -2.0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f (4.0, 3.0, -2.0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (-4.0, 3.0, -2.0);
    glEnd ();

    glPushMatrix ();

    /*GLfloat persp_mat[16] = { 1, 0, -3.845925372767128e-16, 0, 0,
        0.5000000000000003, -5.768888059150692e-16, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    glMultMatrixf (persp_mat);*/
    //[1, 0, -3.845925372767128e-16;
    // 0, 0.3333333333333335, 0.6666666666666663;
    // 0, 0, 1]

    //[1, 0, -3.845925372767128e-16;
    // 0, 0.5000000000000003, -5.768888059150692e-16;
    // 0, 0, 1]

    glTranslatef (_x_pos, _y_pos, 0);
    glScalef (_scale_factor, _scale_factor, _scale_factor);
    glRotatef (_x_rot, 1, 0, 0);
    glRotatef (_y_rot, 0, 1, 0);
    glRotatef (_z_rot, 0, 0, 1);

    glBegin (GL_QUADS);
    glColor3f (0, 1, 1);
    glNormal3f (0, 0, -1);
    glVertex3f (-1, -1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (1, -1, 0);
    glEnd ();

    glBegin (GL_TRIANGLES);
    glColor3f (1, 0, 0);
    glNormal3f (0, -1, 0.707);
    glVertex3f (-1, -1, 0);
    glVertex3f (1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (0, 1, 0);
    glNormal3f (1, 0, 0.707);
    glVertex3f (1, -1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (0, 0, 1);
    glNormal3f (0, 1, 0.707);
    glVertex3f (1, 1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (1, 1, 0);
    glNormal3f (-1, 0, 0.707);
    glVertex3f (-1, 1, 0);
    glVertex3f (-1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glPopMatrix ();
}
