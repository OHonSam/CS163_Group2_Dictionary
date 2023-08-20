#include "deftoword.h"
#include "ui_deftoword.h"

DefToWord::DefToWord(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::DefToWord,parent),
    ui(new Ui::DefToWord)
{
    ui->setupUi(this);
}

DefToWord::~DefToWord()
{
    delete ui;
}

void DefToWord::receiveInput(const std::string &input){
    ui->listWidget->clear();
    std::vector<std::string> v=dict->searchForWord(input);
    for(int i=0; i<v.size(); i++)
        ui->listWidget->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}
