#include "editscreen.h"
#include "ui_editscreen.h"

EditScreen::EditScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,parent),
    ui(new Ui::EditScreen)
{
    ui->setupUi(this);
}

EditScreen::~EditScreen()
{
    delete ui;
}
