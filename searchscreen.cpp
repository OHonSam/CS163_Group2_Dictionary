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

void SearchScreen::receiveInputString(const std::string &input, Search::Type type){
    if(type==Search::ForDef){ // input is a word
        Word* res=dict->searchForDef(input);
        if(res){
            this->input=res->word;
            ui->textBrowser->setHtml(HTML_Creator::toHTML(res));
            if(dict->isInFavList(input)){
                ui->pushButton_setFav->setCheckable(true);
                ui->pushButton_setFav->setIcon(heartFillIcon);
            }
            else{
                ui->pushButton_setFav->setCheckable(false);
                ui->pushButton_setFav->setIcon(heartIcon);
            }

            emit updateHistory();
        }
        else ui->textBrowser->setPlainText("");
    }
    else{ // input is a definition
        // to be continued
    }
}


void SearchScreen::on_pushButton_setFav_clicked(bool checked)
{
    if(ui->textBrowser->toPlainText()==QString()) return;
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

