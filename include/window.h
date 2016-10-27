// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QGridLayout>
#include <QKeyEvent>
#include <QTimer>

#include "acquisition.hpp"
#include "augmentation_widget.h"

namespace Ui {
class Window;
}

class Window : public QWidget {
    Q_OBJECT

    public:
    explicit Window (QWidget* parent = 0);
    ~Window ();

    QSize minimumSizeHint () const;
    QSize sizeHint () const;

    public slots:
    void timeout ();

    protected:
    void keyPressEvent (QKeyEvent* event);

    private:
    unsigned int _framerate = 30;
    acquisition _acquisition;
    QTimer _frame_timer;
    QGridLayout _layout;
    augmentation_widget _augmentation;
};

#endif // WINDOW_H
