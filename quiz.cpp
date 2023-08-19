#include "quiz.h"
#include "ui_quiz.h"

Quiz::Quiz(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Quiz),
    dict(dict)
{
    ui->setupUi(this);
}

Quiz::~Quiz()
{
    delete ui;
}

void Quiz::on_pushButton_title_clicked()
{
    emit switchToHomeScreen();
}

