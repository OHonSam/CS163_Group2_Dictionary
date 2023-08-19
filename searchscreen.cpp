#include "searchscreen.h"
#include "ui_searchscreen.h"

#include <QListView>

SearchScreen::SearchScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Search,parent),
    ui(new Ui::SearchScreen),
    heartIcon(":/img/images/heart.svg"),
    heartFillIcon(":/img/images/heart-fill.svg"),
    input("")
{
    ui->setupUi(this);
}

SearchScreen::~SearchScreen()
{
    delete ui;
}

void SearchScreen::receiveInputString(const std::string &word){
    input=word;
    ui->textBrowser->setHtml(HTML_Creator::toHTML(dict->searchForDef(word)));
    if(dict->isInFavList(word)){
        ui->pushButton_setFav->setCheckable(true);
        ui->pushButton_setFav->setIcon(heartFillIcon);
    }
    else{
        ui->pushButton_setFav->setCheckable(false);
        ui->pushButton_setFav->setIcon(heartIcon);
    }
}


void SearchScreen::on_pushButton_setFav_clicked(bool checked)
{
    if(checked){
        dict->removeFav(input);
        ui->pushButton_setFav->setCheckable(false);
        ui->pushButton_setFav->setIcon(heartIcon);
    }
    else{
        dict->addFav(input);
        ui->pushButton_setFav->setCheckable(true);
        ui->pushButton_setFav->setIcon(heartFillIcon);
    }
    emit updateFavList();
}

