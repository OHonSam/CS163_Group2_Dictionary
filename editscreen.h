#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include <QWidget>

namespace Ui {
class editScreen;
}

class editScreen : public QWidget
{
    Q_OBJECT

public:
    explicit editScreen(QWidget *parent = nullptr);
    ~editScreen();

private:
    Ui::editScreen *ui;
};

#endif // EDITSCREEN_H
