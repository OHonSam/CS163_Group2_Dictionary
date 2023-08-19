#include "homescreen.h"
#include "ui_homescreen.h"

#include <QMessageBox>
#include <QStringListModel>
#include <QListView>
#include "html_creator.h"

HomeScreen::HomeScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Home,parent),
    ui(new Ui::HomeScreen),
    completer(this),
    heartIcon(":/img/images/heart.svg"),
    heartFillIcon(":/img/images/heart-fill.svg")
{
    ui->setupUi(this);

    completer.setCaseSensitivity(Qt::CaseInsensitive);

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

    showDailyWord();
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
        return;
    }
    showDailyWord();
    updateCompleter();
}


void HomeScreen::on_pushButton_HistoryScreen_clicked()
{
    emit switchScreen(Screen::History);
}

void HomeScreen::updateCompleter(){
    QStringListModel *model=qobject_cast<QStringListModel*>(completer.model());
    if(model) delete model;

    model = new QStringListModel(&completer);
    completer.setModel(model);

    suggestions.clear();
    std::vector<std::string> sug = dict->searchPrefix("");
    for(const std::string& str:sug) suggestions<<str.c_str();

    model->setStringList(suggestions);
}


void HomeScreen::on_pushButton_search_clicked()
{
    on_lineEdit_search_returnPressed();
}

void HomeScreen::showDailyWord(){
    Word* w=dict->getDailyWord();
    dailyWord=w->word;
    ui->textBrowser->setHtml(HTML_Creator::toHTML(w));

    if(dict->isInFavList(dailyWord)){
        ui->pushButton_setFav->setCheckable(true);
        ui->pushButton_setFav->setIcon(heartFillIcon);
    }
    else{
        ui->pushButton_setFav->setCheckable(false);
        ui->pushButton_setFav->setIcon(heartIcon);
    }
}

void HomeScreen::on_pushButton_resetDailyWord_clicked()
{
    showDailyWord();
}


void HomeScreen::on_pushButton_FavScreen_clicked()
{
    emit switchScreen(Screen::FavList);
}


void HomeScreen::on_pushButton_EditScreen_clicked()
{
    emit switchScreen(Screen::Edit);
}


void HomeScreen::on_pushButton_AddScreen_clicked()
{
    emit switchScreen(Screen::Add);
}


void HomeScreen::on_pushButton_QuizScreen_clicked()
{
    emit switchScreen(Screen::Quiz);
}


void HomeScreen::on_lineEdit_search_returnPressed()
{
    QString raw_word=ui->lineEdit_search->text();
    std::string word=raw_word.toLower().toLocal8Bit().toStdString();
    if(raw_word.toLower()==QString::fromStdString(word)){
        emit updateHistory(word,true);
        emit sendToSearchScreen(word);
        emit switchScreen(Screen::Search);
    }
    else
        QMessageBox::warning(this,"Invalid input","Your input is not valid. Please type in solely ASCII characters!");
}

void HomeScreen::on_pushButton_setFav_clicked(bool checked)
{
    if(checked){
        dict->removeFav(dailyWord);
        ui->pushButton_setFav->setCheckable(false);
        ui->pushButton_setFav->setIcon(heartIcon);
    }
    else{
        dict->addFav(dailyWord);
        ui->pushButton_setFav->setCheckable(true);
        ui->pushButton_setFav->setIcon(heartFillIcon);
    }
    emit updateFavList();
}

