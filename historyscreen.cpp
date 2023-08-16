#include "historyscreen.h"
#include "ui_historyscreen.h"

HistoryScreen::HistoryScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryScreen),
    dict(dict)
{
    ui->setupUi(this);
}

HistoryScreen::~HistoryScreen()
{
    delete ui;
}
