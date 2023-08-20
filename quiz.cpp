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
    correctId=rand()%NUMC;
    words=dict->getMultiChoices(NUMC);
    if(ui->comboBox->currentIndex()==int(MC::Def)){
        ui->label_ques->setText(QString::fromStdString(words[correctId]->getRandDef()));
        ui->pushButton_c1->setText(QString::fromStdString(words[0]->word));
        ui->pushButton_c2->setText(QString::fromStdString(words[1]->word));
        ui->pushButton_c3->setText(QString::fromStdString(words[2]->word));
        ui->pushButton_c4->setText(QString::fromStdString(words[3]->word));
    }
    else{
        ui->label_ques->setText(QString::fromStdString(words[correctId]->word));
        ui->pushButton_c1->setText(QString::fromStdString(words[0]->getRandDef()));
        ui->pushButton_c2->setText(QString::fromStdString(words[1]->getRandDef()));
        ui->pushButton_c3->setText(QString::fromStdString(words[2]->getRandDef()));
        ui->pushButton_c4->setText(QString::fromStdString(words[3]->getRandDef()));
    }
}

