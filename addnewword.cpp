#include "addnewword.h"
#include "ui_addnewword.h"

AddNewWord::AddNewWord(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewWord),
    dict(dict)
{
    ui->setupUi(this);
}

AddNewWord::~AddNewWord()
{
    delete ui;
}

void AddNewWord::on_pushButton_title_clicked()
{
    emit switchScreen(Screen::Home);
}

