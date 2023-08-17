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

void SearchForKey::receiveWord(const std::string &word){
    ui->lineEdit_search->setText(QString::fromStdString(word));
}

void SearchForKey::on_pushButton_goBack_clicked()
{
    emit goBack();
}

