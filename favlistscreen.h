#ifndef FAVLISTSCREEN_H
#define FAVLISTSCREEN_H

#include "myscreen.h"

namespace Ui {
class FavListScreen;
}

class FavListScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit FavListScreen(Dict *dict, QWidget *parent = nullptr);
    ~FavListScreen();

public slots:
    void update();

private slots:
    void on_pushButton_remove_clicked();

private:
    Ui::FavListScreen *ui;
};

#endif // FAVLISTSCREEN_H
