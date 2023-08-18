#include "searchforkey.h"
#include "ui_cSearch.h"

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

void SearchForKey::on_pushButton_goBack_clicked()
{
    emit goBack();
}

