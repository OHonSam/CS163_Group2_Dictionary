#include "editscreen.h"
#include "ui_editscreen.h"

#include <QMessageBox>

EditScreen::EditScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Edit,parent),
    ui(new Ui::EditScreen),
    oldWord(nullptr)
{
    ui->setupUi(this);
}

EditScreen::~EditScreen()
{
    delete ui;
}

void EditScreen::receiveWord(Word* word){
    oldWord=word;
    newWord=new Word(word);

    ui->lineEdit_word->setText(QString::fromStdString(word->word));

    on_comboBox_POS_currentIndexChanged(ui->comboBox_POS->currentIndex());
}

void EditScreen::on_comboBox_POS_currentIndexChanged(int index)
{
    if(newWord->def[index].empty()){
        ui->plainTextEdit_def->setPlainText("");
        ui->plainTextEdit_def->setPlaceholderText("Empty");
        return;
    }
    QString res="";
    foreach(std::string str,newWord->def[index]) res+="- "+str+"\n";
    ui->plainTextEdit_def->setPlainText(res);
}


void EditScreen::on_pushButton_saveDef_clicked()
{
    QMessageBox::StandardButton rep;
    rep=QMessageBox::question(this,"Confirm",
        "The old definition will not be able to recovered.\nDo you want to save?",
                                QMessageBox::Yes|QMessageBox::No);
    if(rep==QMessageBox::Yes){
        int index=ui->comboBox_POS->currentIndex();
        std::vector<std::string> output;
        QStringList lines=ui->plainTextEdit_def->toPlainText().split('\n');
        foreach(QString line,lines){
            QString trimmedLine = line.trimmed();
            if (!trimmedLine.isEmpty()) {
                std::string value = trimmedLine.mid(2).toStdString();  // Assuming the "- " prefix should be removed
                if(!value.empty()) output.push_back(value);
            }
        }
        if(output.empty() && newWord->type&(1<<index))
            newWord->type^=(1<<index);
        newWord->def[index]=output;
        on_comboBox_POS_currentIndexChanged(index);
        QMessageBox::information(this,"Information","New definition has been saved!");
    }
}


void EditScreen::on_pushButton_saveWord_clicked()
{
    QString raw=ui->lineEdit_word->text().trimmed();
    std::string word=raw.toLower().toLocal8Bit().toStdString();
    if(raw.toLower()==QString::fromStdString(word)){
        if(dict->isInDict(word)){
            QMessageBox::warning(this,"Caution","This word is already existed!");
            ui->lineEdit_word->setText(QString::fromStdString(newWord->word));
        }
        else{
            QMessageBox::StandardButton rep;
            rep=QMessageBox::question(this,"Confirm",
                                        "The old word will not be able to recovered.\nDo you want to save?",
                                        QMessageBox::Yes|QMessageBox::No);
            if(rep==QMessageBox::Yes){
                newWord->word=word;
                on_comboBox_POS_currentIndexChanged(ui->comboBox_POS->currentIndex());
                QMessageBox::information(this,"Information","New word has been saved!");
            }
        }
    }
    else
        QMessageBox::warning(this,"Invalid input","Your input is not valid. Please type in solely ASCII characters!");
}

void EditScreen::on_pushButton_done_clicked()
{
    if(oldWord==nullptr) return;
    dict->updateWord(oldWord,newWord);
    QMessageBox::information(this,"Information","The dictionary has been updated!");
    emit updateCompleter();
}

