#include "homescreen.h"
#include "ui_homescreen.h"

#include <QMessageBox>
#include <QStringListModel>

HomeScreen::HomeScreen(Dict *dict, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen),
    completer(this),
    dict(dict)
{
    ui->setupUi(this);

    completer.setCaseSensitivity(Qt::CaseInsensitive);

    ui->lineEdit_search->setCompleter(&completer);

    updateSuggestion();
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_comboBox_dictVersion_currentIndexChanged(int index)
{
    switch(index){
    case 0: // EE
        dict->switchDataSet(DataSet::EE);
        break;
    case 1: // EV
        dict->switchDataSet(DataSet::EV);
        break;
    case 2: // VE
        dict->switchDataSet(DataSet::VE);
        break;
    case 3: // Slang
        dict->switchDataSet(DataSet::Slang);
        break;
    case 4: // Emoji
        dict->switchDataSet(DataSet::Emoji);
        break;
    default:
        QMessageBox::warning(this,"Warning","This dictionary does not have your version choice!");
        break;
    }
}


void HomeScreen::on_pushButton_HistoryScreen_clicked()
{
    emit switchToHistoryScreen();
}

void HomeScreen::updateSuggestion(){
    QStringListModel *model=qobject_cast<QStringListModel*>(completer.model());
    if(!model) {
        model = new QStringListModel(&completer);
        completer.setModel(model);
    }

    suggestions.clear();
    std::vector<std::string> sug = dict->searchPrefix("");
    for(const std::string& str:sug) suggestions<<str.c_str();

    model->setStringList(suggestions);
}


void HomeScreen::on_pushButton_search_clicked()
{
    emit updateHistory(ui->lineEdit_search->text().toLower().toStdString(),true);
}

