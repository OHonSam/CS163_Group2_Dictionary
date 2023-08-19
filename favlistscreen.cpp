#include "favlistscreen.h"
#include "ui_favlistscreen.h"

FavListScreen::FavListScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,parent),
    ui(new Ui::FavListScreen)
{
    ui->setupUi(this);
}

FavListScreen::~FavListScreen()
{
    delete ui;
}

