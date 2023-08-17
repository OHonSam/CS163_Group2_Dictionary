#include "searchforkey.h"
#include "ui_searchforkey.h"

SearchForKey::SearchForKey(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForKey),
    dict(dict)
{
    ui->setupUi(this);
}

SearchForKey::~SearchForKey()
{
    delete ui;
}
