#include "favlistscreen.h"
#include "ui_favlistscreen.h"

FavListScreen::FavListScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::FavList,parent),
    ui(new Ui::FavListScreen)
{
    ui->setupUi(this);

    update();
}

FavListScreen::~FavListScreen()
{
    delete ui;
}

void FavListScreen::update(){
    ui->listWidget->clear();
    std::vector<std::string> v=dict->getFav();
    for(int i=0; i<v.size(); i++)
        ui->listWidget->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}


void FavListScreen::on_pushButton_remove_clicked()
{
    int delItem = ui->listWidget->currentRow();

    if(0<=delItem && delItem<ui->listWidget->count()){
        QString word=ui->listWidget->item(delItem)->text();
        dict->removeFav(word.mid(word.indexOf(' ')+1).toStdString());
        update();
    }
}


void FavListScreen::on_pushButton_clear_clicked()
{
    dict->clearFavList();
    update();
}


void FavListScreen::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString word=item->text();
    emit sendToSearchScreen(word.mid(word.indexOf(' ')+1).toStdString());
    emit switchScreen(Screen::Search);
}

