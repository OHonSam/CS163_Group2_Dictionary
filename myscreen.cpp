#include "myscreen.h"

MyScreen::MyScreen(Dict *dict, Screen::Type type, QWidget *parent) :
    QWidget(parent), dict(dict), typeScreen(type)
{
}

void MyScreen::on_pushButton_title_clicked()
{
    emit switchScreen(Screen::Home);
}
