#include "searchscreen.h"
#include "ui_searchscreen.h"

#include <QListView>

SearchScreen::SearchScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Search,parent),
    ui(new Ui::SearchScreen)
{
    ui->setupUi(this);
}

SearchScreen::~SearchScreen()
{
    delete ui;
}

void SearchScreen::receiveInputString(const std::string &word){
    ui->textBrowser->setHtml(HTML_Creator::toHTML(dict->searchForDef(word)));
}

