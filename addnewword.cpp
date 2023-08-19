#include "addnewword.h"
#include "ui_addnewword.h"

AddNewWord::AddNewWord(Dict *dict, QWidget *parent) :
    MyScreen(dict,parent),
    ui(new Ui::AddNewWord)
{
    ui->setupUi(this);
}

AddNewWord::~AddNewWord()
{
    delete ui;
}

