#include "searchfordef.h"
#include "ui_searchfordef.h"

SearchForDef::SearchForDef(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForDef)
{
    ui->setupUi(this);
}

SearchForDef::~SearchForDef()
{
    delete ui;
}
