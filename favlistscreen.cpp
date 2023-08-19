#include "favlistscreen.h"
#include "ui_favlistscreen.h"

FavListScreen::FavListScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavListScreen),
    dict(dict)
{
    ui->setupUi(this);
}

FavListScreen::~FavListScreen()
{
    delete ui;
}

void FavListScreen::on_pushButton_title_clicked()
{
    emit switchToHomeScreen();
}

