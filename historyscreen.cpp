#include "historyscreen.h"
#include "ui_historyscreen.h"

HistoryScreen::HistoryScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::History,parent),
    ui(new Ui::HistoryScreen)
{
    ui->setupUi(this);

    ui->listWidget->clear();

    update();
}

HistoryScreen::~HistoryScreen()
{
    delete ui;
}

void HistoryScreen::update(){
    ui->listWidget->clear();
    std::vector<std::string> v=dict->getHistory();
    for(int i=0; i<v.size(); i++)
        ui->listWidget->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}


void HistoryScreen::on_pushButton_clear_clicked()
{
    dict->clearAllHistory();
    update();
}


void HistoryScreen::on_pushButton_remove_clicked()
{
    int delItem = ui->listWidget->currentRow();

    if(0<=delItem && delItem<ui->listWidget->count()){
        QString word=ui->listWidget->item(delItem)->text();
        dict->removeHistory(word.mid(word.indexOf(' ')+1).toStdString());
        update();
    }
}
