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
    Count
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

protected:
    Dict *dict;
    const Screen::Type typeScreen;
};

#endif // MYSCREEN_H
