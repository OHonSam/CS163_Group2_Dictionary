#include "quiz.h"
#include "ui_quiz.h"

Quiz::Quiz(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Quiz,parent),
    ui(new Ui::Quiz)
{
    ui->setupUi(this);
    on_pushButton_newQuiz_clicked();
}

Quiz::~Quiz()
{
    delete ui;
}


void Quiz::on_pushButton_newQuiz_clicked()
{
    QString tmp;
    correctId=rand()%NUMC;
    words=dict->getMultiChoices(NUMC);
    if(ui->comboBox->currentIndex()==int(MC::Def)){
        tmp=QString::fromStdString(words[correctId]->getRandDef());
        ui->label_ques->setText(tmp);
        ui->label_ques->setToolTip(tmp);
        for(int i=0; i<NUMC; i++){
            tmp=QString::fromStdString(words[i]->word);
            getButton(i)->setText(tmp);
            getButton(i)->setToolTip(tmp);
        }
    }
    else{
        tmp=QString::fromStdString(words[correctId]->word);
        ui->label_ques->setText(tmp);
        ui->label_ques->setToolTip(tmp);
        for(int i=0; i<NUMC; i++){
            tmp=QString::fromStdString(words[i]->getRandDef());
            getButton(i)->setText(tmp);
            getButton(i)->setToolTip(tmp);
        }
    }

    for(int i=0; i<NUMC; i++) getButton(i)->setStyleSheet(normalStyle);
}


void Quiz::on_pushButton_c0_clicked()
{
    considerChoice(0);
}

QPushButton* Quiz::getButton(int id){
    switch(id){
    case 0: return ui->pushButton_c0; break;
    case 1: return ui->pushButton_c1; break;
    case 2: return ui->pushButton_c2; break;
    case 3: return ui->pushButton_c3; break;
    }
    return nullptr;
}

void Quiz::considerChoice(int id){
    getButton(correctId)->setStyleSheet(correctStyle);
    if(id!=correctId) getButton(id)->setStyleSheet(incorrectStyle);
}

void Quiz::on_pushButton_c1_clicked()
{
    considerChoice(1);
}


void Quiz::on_pushButton_c2_clicked()
{
    considerChoice(2);
}


void Quiz::on_pushButton_c3_clicked()
{
    considerChoice(3);
}
