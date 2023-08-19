#include "editscreen.h"
#include "ui_editscreen.h"

EditScreen::EditScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditScreen),
    dict(dict)
{
    ui->setupUi(this);
}

EditScreen::~EditScreen()
{
    delete ui;
}

void EditScreen::on_pushButton_title_clicked()
{
    emit switchScreen(Screen::Home);
}

