#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen),
    dict(dict)
{
    ui->setupUi(this);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}
