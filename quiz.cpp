#include "quiz.h"
#include "ui_quiz.h"

Quiz::Quiz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Quiz)
{
    ui->setupUi(this);
}

Quiz::~Quiz()
{
    delete ui;
}
