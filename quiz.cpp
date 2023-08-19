#include "quiz.h"
#include "ui_quiz.h"

Quiz::Quiz(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Quiz,parent),
    ui(new Ui::Quiz)
{
    ui->setupUi(this);
}

Quiz::~Quiz()
{
    delete ui;
}

