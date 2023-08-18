#ifndef A_H
#define A_H

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

#endif // A_H
