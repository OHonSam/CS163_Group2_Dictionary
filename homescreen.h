#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(Dict *dict, QWidget *parent = nullptr);
    ~HomeScreen();

private:
    Ui::HomeScreen *ui;

    Dict *dict;
};

#endif // HOMESCREEN_H
