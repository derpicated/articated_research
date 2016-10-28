// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QSlider>

namespace Ui {
class Window;
}

class Window : public QWidget {
    Q_OBJECT

    public:
    explicit Window (QWidget* parent = 0);
    ~Window ();

    public slots:
    void scaleSlider_valueChanged (int new_value);
    void posXSlider_valueChanged (int new_value);
    void posYSlider_valueChanged (int new_value);
    void rotXSlider_valueChanged (int new_value);
    void rotYSlider_valueChanged (int new_value);
    void rotZSlider_valueChanged (int new_value);

    protected:
    void keyPressEvent (QKeyEvent* event);

    private:
    Ui::Window* ui;
};

#endif // WINDOW_H
