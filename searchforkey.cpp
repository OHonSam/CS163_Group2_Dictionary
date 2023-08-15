#include "searchforkey.h"
#include "ui_searchforkey.h"

SearchForKey::SearchForKey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForKey)
{
    ui->setupUi(this);
}

SearchForKey::~SearchForKey()
{
    delete ui;
}
