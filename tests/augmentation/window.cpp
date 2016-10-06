// window.cpp

#include "window.h"
#include "ui_window.h"

#include "augmentation_widget.h"

Window::Window (QWidget* parent)
: QWidget (parent)
, ui (new Ui::Window) {
    ui->setupUi (this);

    connect (ui->posXSlider, SIGNAL (valueChanged (int)), ui->testWidget,
    SLOT (setXPosition (int)));
    connect (ui->posYSlider, SIGNAL (valueChanged (int)), ui->testWidget,
    SLOT (setYPosition (int)));

    connect (ui->testWidget, SIGNAL (xRotationChanged (int)), ui->rotXSlider,
    SLOT (setValue (int)));
    connect (ui->testWidget, SIGNAL (yRotationChanged (int)), ui->rotYSlider,
    SLOT (setValue (int)));
    connect (ui->testWidget, SIGNAL (zRotationChanged (int)), ui->rotZSlider,
    SLOT (setValue (int)));
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
