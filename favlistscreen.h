#ifndef FAVLISTSCREEN_H
#define FAVLISTSCREEN_H

#include <QWidget>

namespace Ui {
class favlistscreen;
}

class favlistscreen : public QWidget
{
    Q_OBJECT

public:
    explicit favlistscreen(QWidget *parent = nullptr);
    ~favlistscreen();

private:
    Ui::favlistscreen *ui;
};

#endif // FAVLISTSCREEN_H
