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
    std::vector<std::string> v=dict->getHistory();
    for(int i=0; i<v.size(); i++)
        ui->listWidget_history->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}

void HistoryScreen::updateHistory(const std::string& word, bool isAdd){
    if(isAdd) dict->addHistory(word); else dict->removeHistory(word);
    update();
}

