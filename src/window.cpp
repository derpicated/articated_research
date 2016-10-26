// window.cpp

#include "window.h"

Window::Window (QWidget* parent)
: QWidget (parent)
, aug_widget (this) {
}

Window::~Window () {
}

void Window::keyPressEvent (QKeyEvent* e) {
    if (e->key () == Qt::Key_Escape)
        close ();
    else
        QWidget::keyPressEvent (e);
}
