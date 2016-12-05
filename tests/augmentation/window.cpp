// window.cpp
#include <math.h>

#include "ui_window.h"
#include "window.h"

#include "augmentation_widget.h"

#ifndef SAMPLES_DIR
#define SAMPLES_DIR ""
#endif

Window::Window (QWidget* parent)
: QWidget (parent)
, ui (new Ui::Window) {
    ui->setupUi (this);

    connect (ui->loadButton, SIGNAL (clicked ()), this, SLOT (loadButton_clicked ()));

    connect (ui->scaleSlider, SIGNAL (valueChanged (int)), this,
    SLOT (scaleSlider_valueChanged (int)));
    connect (ui->posXSlider, SIGNAL (valueChanged (int)), this,
    SLOT (posXSlider_valueChanged (int)));
    connect (ui->posYSlider, SIGNAL (valueChanged (int)), this,
    SLOT (posYSlider_valueChanged (int)));

    connect (ui->rotXSlider, SIGNAL (valueChanged (int)), this,
    SLOT (rotXSlider_valueChanged (int)));
    connect (ui->rotYSlider, SIGNAL (valueChanged (int)), this,
    SLOT (rotYSlider_valueChanged (int)));
    connect (ui->rotZSlider, SIGNAL (valueChanged (int)), this,
    SLOT (rotZSlider_valueChanged (int)));
}

Window::~Window () {
    delete ui;
}

void Window::keyPressEvent (QKeyEvent* e) {
    if (e->key () == Qt::Key_Escape)
        close ();
    else
        QWidget::keyPressEvent (e);
}

void Window::loadButton_clicked () {
    ui->testWidget->loadObject (
    std::string (SAMPLES_DIR) + std::string ("/teapot.obj"));
}

void Window::scaleSlider_valueChanged (int new_value) {
    ui->testWidget->setScale (((float)new_value) / 100);
    ui->testWidget->update ();
}
void Window::posXSlider_valueChanged (int new_value) {
    ui->testWidget->setXPosition (((float)new_value) / 100);
    ui->testWidget->update ();
}
void Window::posYSlider_valueChanged (int new_value) {
    ui->testWidget->setYPosition (((float)new_value) / 100);
    ui->testWidget->update ();
}

void Window::rotXSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    angle_to_matrix (persp_mat, new_value, 1, 0, 0);
    ui->testWidget->setXRotation (persp_mat);
    ui->testWidget->update ();
}
void Window::rotYSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    angle_to_matrix (persp_mat, new_value, 0, 1, 0);
    ui->testWidget->setYRotation (persp_mat);
    ui->testWidget->update ();
}
void Window::rotZSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    angle_to_matrix (persp_mat, new_value, 0, 0, 1);
    ui->testWidget->setZRotation (persp_mat);
    ui->testWidget->update ();
}

/*derived from  https://www.opengl.org/sdk/docs/man2/xhtml/glRotate.xml*/
void Window::angle_to_matrix (float mat[16], float angle, float x, float y, float z) {
    float deg2rad = 3.14159265f / 180.0f;
    float c       = cosf (angle * deg2rad);
    float s       = sinf (angle * deg2rad);
    float c1      = 1.0f - c;

    // build rotation matrix
    mat[0]  = (x * x * c1) + c;
    mat[1]  = (x * y * c1) - (z * s);
    mat[2]  = (x * z * c1) + (y * s);
    mat[3]  = 0;
    mat[4]  = (y * x * c1) + (z * s);
    mat[5]  = (y * y * c1) + c;
    mat[6]  = (y * z * c1) - (x * s);
    mat[7]  = 0;
    mat[8]  = (z * x * c1) - (y * s);
    mat[9]  = (z * y * c1) + (x * s);
    mat[10] = (z * z * c1) + c;
    mat[11] = 0;
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;
}
