#include "editscreen.h"
#include "ui_editscreen.h"

#include <QMessageBox>

EditScreen::EditScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Edit,parent),
    ui(new Ui::EditScreen)
{
    ui->setupUi(this);
}

EditScreen::~EditScreen()
{
    delete ui;
}

void EditScreen::receiveWord(Word* word){
    curWord=word;

    ui->lineEdit_word->setText(QString::fromStdString(word->word));

    on_comboBox_POS_currentIndexChanged(ui->comboBox_POS->currentIndex());
}

void EditScreen::on_comboBox_POS_currentIndexChanged(int index)
{
    if(curWord->def[index].empty()){
        ui->plainTextEdit_def->setPlainText("");
        ui->plainTextEdit_def->setPlaceholderText("Empty");
        return;
    }
    QString res="";
    foreach(std::string str,curWord->def[index]) res+="- "+str+"\n";
    ui->plainTextEdit_def->setPlainText(res);
}


void EditScreen::on_pushButton_saveDef_clicked()
{
    QMessageBox::StandardButton rep;
    rep=QMessageBox::question(this,"Confirm",
        "The old definition will not be able to recovered.\nDo you want to save?",
                                QMessageBox::Yes|QMessageBox::No);
    if(rep==QMessageBox::Yes){
        std::vector<std::string> output;
        QStringList lines=ui->plainTextEdit_def->toPlainText().split('\n');
        foreach(QString line,lines){
            QString trimmedLine = line.trimmed();
            if (!trimmedLine.isEmpty()) {
                QString value = trimmedLine.mid(2);  // Assuming the "- " prefix should be removed
                output.push_back(value.toStdString());
            }
        }
        curWord->def[ui->comboBox_POS->currentIndex()]=output;
        on_comboBox_POS_currentIndexChanged(ui->comboBox_POS->currentIndex());
        QMessageBox::information(this,"Information","New definition has been saved!");
    }
}


void EditScreen::on_pushButton_saveWord_clicked()
{
    QString raw=ui->lineEdit_word->text();
    std::string word=raw.toLower().toLocal8Bit().toStdString();
    if(raw.toLower()==QString::fromStdString(word)){
        QMessageBox::StandardButton rep;
        rep=QMessageBox::question(this,"Confirm",
                                    "The old word will not be able to recovered.\nDo you want to save?",
                                    QMessageBox::Yes|QMessageBox::No);
        if(rep==QMessageBox::Yes){
            curWord->word=word;
            on_comboBox_POS_currentIndexChanged(ui->comboBox_POS->currentIndex());
            QMessageBox::information(this,"Information","New word has been saved!");
        }
    }
    else
        QMessageBox::warning(this,"Invalid input","Your input is not valid. Please type in solely ASCII characters!");
}

