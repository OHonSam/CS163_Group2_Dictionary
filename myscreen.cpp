#include "myscreen.h"

MyScreen::MyScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    dict(dict)
{
}

void MyScreen::on_pushButton_title_clicked()
{
    emit switchScreen(Screen::Home);
}
