#include "historyscreen.h"
#include "ui_historyscreen.h"

#include <QMessageBox>

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
    for(int i=0, cnt=0; i<v.size(); i++)
        if(v[i]!="")
            ui->listWidget->addItem(QString::number(++cnt)+". "+QString::fromStdString(v[i]));
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

void HistoryScreen::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString raw=item->text();
    std::string word=raw.mid(raw.indexOf(' ')+1).toStdString();
    if(!dict->isInDict(word)){
        QMessageBox::StandardButton rep=QMessageBox::warning(this,"Error",
            "This word is not existed in dictionary.\nDo you want to remove it?",
            QMessageBox::Yes|QMessageBox::No
        );
        if(rep==QMessageBox::Yes){
            on_pushButton_remove_clicked();
            QMessageBox::information(this,"Information","The word has been removed!");
        }
    }
    else{
        emit sendToSearchScreen(word);
        emit switchScreen(Screen::Search);
    }
}

