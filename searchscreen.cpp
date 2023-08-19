#include "searchscreen.h"
#include "ui_searchscreen.h"

#include <QListView>

SearchScreen::SearchScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,parent),
    ui(new Ui::SearchScreen)
{
    ui->setupUi(this);
}

SearchScreen::~SearchScreen()
{
    delete ui;
}

void SearchScreen::receiveWord(const std::string &word){
    ui->textBrowser->setHtml(HTML_Creator::toHTML(dict->searchForDef(word)));
}

void SearchScreen::on_pushButton_goBack_clicked()
{
    emit goBack();
}

