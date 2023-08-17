#include "editscreen.h"
#include "ui_editscreen.h"

editScreen::editScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editScreen)
{
    ui->setupUi(this);
}

editScreen::~editScreen()
{
    delete ui;
}
