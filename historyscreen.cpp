#include "historyscreen.h"
#include "ui_historyscreen.h"

HistoryScreen::HistoryScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryScreen),
    dict(dict)
{
    ui->setupUi(this);

    ui->listWidget_history->clear();

    update();
}

HistoryScreen::~HistoryScreen()
{
    delete ui;
}

void HistoryScreen::on_pushButton_goBack_clicked()
{
    emit goBack();
}

void HistoryScreen::update(){
    ui->listWidget_history->clear();
    std::vector<std::string> v=dict->getHistory();
    for(int i=0; i<v.size(); i++)
        ui->listWidget_history->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}

void HistoryScreen::updateHistory(const std::string& word, bool isAdd){
    if(isAdd) dict->addHistory(word); else dict->removeHistory(word);
    update();
}


void HistoryScreen::on_pushButton_clear_clicked()
{
    dict->clearAllHistory();
    update();
}


void HistoryScreen::on_pushButton_remove_clicked()
{
    int delItem = ui->listWidget_history->currentRow();

    if(0<=delItem && delItem<ui->listWidget_history->count()){
        QString word=ui->listWidget_history->item(delItem)->text();
        dict->removeHistory(word.mid(word.indexOf(' ')+1).toStdString());
        update();
    }
}

