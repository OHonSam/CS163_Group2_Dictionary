#include "searchres.h"
#include "ui_dSearch.h"

searchRes::searchRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchRes)
{
    ui->setupUi(this);
}

searchRes::~searchRes()
{
    delete ui;
}