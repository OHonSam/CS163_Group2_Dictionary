#include "editchoice.h"
#include "ui_editchoice.h"

EditChoice::EditChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditChoice)
{
    ui->setupUi(this);
}

EditChoice::~EditChoice()
{
    delete ui;
}
