#include "deftoword.h"
#include "ui_deftoword.h"

DefToWord::DefToWord(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::DefToWord),
    ui(new Ui::DefToWord)
{
    ui->setupUi(this);
}

DefToWord::~DefToWord()
{
    delete ui;
}
