#include "searchscreen.h"
#include "ui_searchscreen.h"

#include <QListView>

SearchScreen::SearchScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Search,parent),
    ui(new Ui::SearchScreen),
    heartIcon(":/img/images/heart.svg"),
    heartFillIcon(":/img/images/heart-fill.svg"),
    word(nullptr)
{
    ui->setupUi(this);
}

SearchScreen::~SearchScreen()
{
    delete ui;
}

void SearchScreen::receiveInputString(const std::string &input, Search::Type type){
    if(type==Search::ForDef){ // input is a word
        word=dict->searchForDef(input);
        if(word){
            ui->textBrowser->setHtml(HTML_Creator::toHTML(word));
            if(dict->isInFavList(word->word)){
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
    if(!word) return;
    if(checked){
        dict->removeFav(word->word);
        ui->pushButton_setFav->setCheckable(false);
        ui->pushButton_setFav->setIcon(heartIcon);
    }
    else{
        dict->addFav(word->word);
        ui->pushButton_setFav->setCheckable(true);
        ui->pushButton_setFav->setIcon(heartFillIcon);
    }
    emit updateFavList();
}


void SearchScreen::on_pushButton_edit_clicked()
{
    if(!word) return;
    emit sendToEditScreen(word);
    emit switchScreen(Screen::Edit);
}

