#include "homescreen.h"
#include "ui_homescreen.h"

#include <QMessageBox>

HomeScreen::HomeScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen),
    dict(dict)
{
    ui->setupUi(this);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_comboBox_dictVersion_currentIndexChanged(int index)
{
    switch(index){
    case 0: // EE
        dict->switchDataSet(DataSet::EE);
        break;
    case 1: // EV
        dict->switchDataSet(DataSet::EV);
        break;
    case 2: // VE
        dict->switchDataSet(DataSet::VE);
        break;
    case 3: // Slang
        dict->switchDataSet(DataSet::Slang);
        break;
    case 4: // Emoji
        dict->switchDataSet(DataSet::Emoji);
        break;
    default:
        QMessageBox::warning(this,"Warning","This dictionary does not have your version choice!");
        break;
    }
}


void HomeScreen::on_pushButton_HistoryScreen_clicked()
{
    emit switchToHistoryScreen();
}

