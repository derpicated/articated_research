// window.cpp

#include "window.h"
#include "ui_window.h"

#include "augmentation_widget.h"

Window::Window (QWidget* parent)
: QWidget (parent)
, ui (new Ui::Window) {
    ui->setupUi (this);

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

void Window::scaleSlider_valueChanged (int new_value) {
    ui->testWidget->setScale (((float)new_value) / 100);
}
void Window::posXSlider_valueChanged (int new_value) {
    ui->testWidget->setXPosition (((float)new_value) / 100);
}
void Window::posYSlider_valueChanged (int new_value) {
    ui->testWidget->setYPosition (((float)new_value) / 100);
}

void Window::rotXSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    ui->testWidget->setXRotation (persp_mat);
}
void Window::rotYSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    ui->testWidget->setYRotation (persp_mat);
}
void Window::rotZSlider_valueChanged (int new_value) {
    GLfloat persp_mat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    ui->testWidget->setZRotation (persp_mat);
}
