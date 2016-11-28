// augmentation_widget.cpp

#include "augmentation_widget.h"
#include <GL/gl.h>

// clang-format off
#define MATRIX_INITVAL  1, 0, 0, 0,\
                        0, 1, 0, 0,\
                        0, 0, 1, 0,\
                        0, 0, 0, 1
// clang-format on

augmentation_widget::augmentation_widget (QWidget* parent)
: QOpenGLWidget (parent)
, _scale_factor (1.0f)
, _x_pos (0.0f)
, _y_pos (0.0f)
, _x_persp_mat{ MATRIX_INITVAL }
, _y_persp_mat{ MATRIX_INITVAL }
, _z_persp_mat{ MATRIX_INITVAL } {
}

augmentation_widget::~augmentation_widget () {
}

QSize augmentation_widget::minimumSizeHint () const {
    return QSize (100, 100);
}

QSize augmentation_widget::sizeHint () const {
    return QSize (500, 500);
}

void augmentation_widget::setBackground (GLvoid* image, GLsizei width, GLsizei height) {
    // create background texture
    glBindTexture (GL_TEXTURE_2D, _texture_background);
    // TODO: maybe move these to init?
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
}

void augmentation_widget::setScale (const float scale) {
    _scale_factor = scale;
}

void augmentation_widget::setXPosition (const float location) {
    _x_pos = location;
}

void augmentation_widget::setYPosition (const float location) {
    _y_pos = location;
}

void augmentation_widget::setXRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _x_persp_mat[i] = persp_mat[i];
    }
}

void augmentation_widget::setYRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _x_persp_mat[i] = persp_mat[i];
    }
}

void augmentation_widget::setZRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _x_persp_mat[i] = persp_mat[i];
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

    glTranslatef (_x_pos, _y_pos, 0);
    glScalef (_scale_factor, _scale_factor, _scale_factor);
    glMultMatrixf (_x_persp_mat);
    glMultMatrixf (_y_persp_mat);
    glMultMatrixf (_z_persp_mat);
    // glRotatef (_x_rot, 1, 0, 0);
    // glRotatef (_y_rot, 0, 1, 0);
    // glRotatef (_z_rot, 0, 0, 1);*/

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
