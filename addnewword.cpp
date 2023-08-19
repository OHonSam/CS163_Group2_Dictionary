#include "addnewword.h"
#include "ui_baddnewword.h"

AddNewWord::AddNewWord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditScreen)
{
    ui->setupUi(this);
}

AddNewWord::~AddNewWord()
{
    delete ui;
}
