// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QSlider>

#include "augmentation_widget.h"

namespace Ui {
class Window;
}

class Window : public QWidget {
    Q_OBJECT

    public:
    explicit Window (QWidget* parent = 0);
    ~Window ();

    public slots:

    protected:
    void keyPressEvent (QKeyEvent* event);

    private:
    augmentation_widget aug_widget;
};

#endif // WINDOW_H
