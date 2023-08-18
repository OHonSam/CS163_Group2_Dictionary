#include "favlistscreen.h"
#include "ui_favlistscreen.h"

favlistscreen::favlistscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::favlistscreen)
{
    ui->setupUi(this);
}

favlistscreen::~favlistscreen()
{
    delete ui;
}
