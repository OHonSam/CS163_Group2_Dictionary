#include "viewscreen.h"
#include "ui_viewscreen.h"

viewScreen::viewScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewScreen)
{
    ui->setupUi(this);
}

viewScreen::~viewScreen()
{
    delete ui;
}
