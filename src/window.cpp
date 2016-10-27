// window.cpp

#include "window.h"

Window::Window (QWidget* parent)
: QWidget (parent)
, _acquisition ()
, _frame_timer (this)
, _layout (this)
, _augmentation (this) {
    _layout.addWidget (&_augmentation, 0, 0);

    connect (&_frame_timer, SIGNAL (timeout ()), this, SLOT (timeout ()));
    _frame_timer.setInterval (1000 / _framerate);
    _frame_timer.start ();

    _acquisition.source (
    std::string (SAMPLES_DIR) + std::string ("/3_markers_good.webm"));
}

Window::~Window () {
}

QSize Window::minimumSizeHint () const {
    return QSize (100, 100);
}

QSize Window::sizeHint () const {
    return QSize (500, 500);
}

void Window::keyPressEvent (QKeyEvent* e) {
    if (e->key () == Qt::Key_Escape)
        close ();
    else
        QWidget::keyPressEvent (e);
}

void Window::timeout () {
    cv::Mat frame = _acquisition.capture ();
    _augmentation.setBackground (frame.ptr (), frame.cols, frame.rows);
    _augmentation.update ();
}
