#include "historyscreen.h"
#include "ui_historyscreen.h"

HistoryScreen::HistoryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryScreen)
{
    ui->setupUi(this);
}

HistoryScreen::~HistoryScreen()
{
    delete ui;
}
