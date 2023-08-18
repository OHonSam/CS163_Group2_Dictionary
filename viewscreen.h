#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include <QWidget>

namespace Ui {
class viewScreen;
}

class viewScreen : public QWidget
{
    Q_OBJECT

public:
    explicit viewScreen(QWidget *parent = nullptr);
    ~viewScreen();

private:
    Ui::viewScreen *ui;
};

#endif // VIEWSCREEN_H
