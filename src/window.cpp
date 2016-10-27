// window.cpp

#include "window.h"

Window::Window (QWidget* parent)
: QWidget (parent)
, _acquisition ()
, _frame_timer ()
, _holder_layout_img (this)
, _holder_layout_btn (this)
, _layout_app (QBoxLayout::TopToBottom, this)
, _layout_img (&_holder_layout_img)
, _layout_btn (QBoxLayout::LeftToRight, &_holder_layout_btn)
, _btn_pause ("Pause", this)
, _btn_reference ("Set Reference", this)
, _btn_input ("Select Input", this)
, _statusbar (this)
, _augmentation (this) {
    _layout_app.addWidget (&_holder_layout_img);
    _layout_app.addWidget (&_holder_layout_btn);
    _layout_app.addWidget (&_statusbar);

    _layout_img.addWidget (&_augmentation, 0, 0);

    _layout_btn.addWidget (&_btn_pause);
    _layout_btn.addWidget (&_btn_reference);
    _layout_btn.addWidget (&_btn_input);

    _statusbar.showMessage ("Welcome");
    _statusbar.setSizeGripEnabled (false);

    connect (&_frame_timer, SIGNAL (timeout ()), this, SLOT (timeout ()));
    connect (&_btn_pause, SIGNAL (clicked ()), this, SLOT (btn_pause_clicked ()));
    connect (&_btn_reference, SIGNAL (clicked ()), this, SLOT (btn_reference_clicked ()));
    connect (&_btn_input, SIGNAL (clicked ()), this, SLOT (btn_input_clicked ()));

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

void Window::btn_pause_clicked () {
    if (_frame_timer.isActive ()) {
        _frame_timer.stop ();
        _btn_pause.setText ("Resume");
    } else {
        _frame_timer.start ();
        _btn_pause.setText ("Pause");
    }
}

void Window::btn_reference_clicked () {
    // call vision here
    ;
}

void Window::btn_input_clicked () {
    // select input here
    ;
}
