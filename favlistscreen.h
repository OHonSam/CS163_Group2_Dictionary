#ifndef FAVLISTSCREEN_H
#define FAVLISTSCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class FavListScreen;
}

class FavListScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FavListScreen(Dict *dict, QWidget *parent = nullptr);
    ~FavListScreen();

signals:
    void switchToHomeScreen();

private slots:
    void on_pushButton_title_clicked();

private:
    Ui::FavListScreen *ui;
    Dict *dict;
};

#endif // FAVLISTSCREEN_H
