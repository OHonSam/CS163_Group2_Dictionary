#include "searchfordef.h"
#include "ui_searchfordef.h"

#include <QListView>

SearchForDef::SearchForDef(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForDef),
    dict(dict),
    completer(this)
{
    ui->setupUi(this);

    // setting completer
    ui->lineEdit_search->setCompleter(&completer);

    QListView *popupListView = qobject_cast<QListView *>(completer.popup());
    if (popupListView) {
        popupListView->setStyleSheet("QListView {"
                                     "  padding: 9px;"
                                     "  border-color: rgb(77, 101, 246);"
                                     "  border-width : 1px;"
                                     "  border-style:inset;"
                                     "  border-radius: 8px;"
                                     "  min-height: 1px;"
                                     "  min-width: 1px;"
                                     "  background-color: rgb(102, 124, 246);"
                                     "  color: white;"
                                     "  selection-color: rgb(39, 182, 240);"
                                     "  selection-background-color: rgb(77, 92, 245);"
                                     "  font: 11pt \"Comfortaa\";"
                                     "}"
                                     );
    }

    updateCompleter();
}

SearchForDef::~SearchForDef()
{
    delete ui;
}

void SearchForDef::receiveWord(const std::string &word){
    ui->lineEdit_search->setText(QString::fromStdString(word));
    ui->textBrowser->setHtml(HTML_Creator::toHTML(dict->searchForDef(word)));
}

void SearchForDef::on_pushButton_goBack_clicked()
{
    emit goBack();
}

void SearchForDef::updateCompleter(){
    QStringListModel *model=qobject_cast<QStringListModel*>(completer.model());
    if(model) delete model;

    model = new QStringListModel(&completer);
    completer.setModel(model);

    suggestions.clear();
    std::vector<std::string> sug = dict->searchPrefix("");
    for(const std::string& str:sug) suggestions<<str.c_str();

    model->setStringList(suggestions);
}


void SearchForDef::on_pushButton_search_clicked()
{
    ui->textBrowser->setHtml(HTML_Creator::toHTML(dict->searchForDef(
        ui->lineEdit_search->text().toStdString()
    )));
}

