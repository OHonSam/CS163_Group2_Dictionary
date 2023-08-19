#ifndef MYSCREEN_H
#define MYSCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Screen{
enum Type{
    Dummy,
    Home,
    History,
    Search,
    FavList,
    Edit,
    Add,
    Quiz,
    GoBack, // Not a screen and below, use for a signal
};
}

namespace Search{
enum Type{
    ForDef,
    ForWord
};
}

class MyScreen: public QWidget
{
    Q_OBJECT
public:
    explicit MyScreen(Dict *dict, Screen::Type type, QWidget *parent = nullptr);

signals:
    void switchScreen(Screen::Type id);

protected slots:
    void on_pushButton_title_clicked();
    void on_pushButton_goBack_clicked(); // not in home screen, produce warning but can ignore it

protected:
    Dict *dict;
    const Screen::Type typeScreen;
};

#endif // MYSCREEN_H
