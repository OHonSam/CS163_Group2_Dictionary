#include "addnewword.h"
#include "ui_addnewword.h"

#include <QMessageBox>

AddNewWord::AddNewWord(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::Add,parent),
    ui(new Ui::AddNewWord),
    newWord(new Word())
{
    ui->setupUi(this);
}

AddNewWord::~AddNewWord()
{
    delete ui;
    if(newWord && dict->searchForDef(newWord->word)!=newWord) delete newWord;
}

void AddNewWord::on_pushButton_discard_clicked()
{
    if(dict->searchForDef(newWord->word)!=newWord) delete newWord;
    newWord=new Word();
    ui->lineEdit_word->setText("");
    ui->plainTextEdit_def->setPlainText("");
}


void AddNewWord::on_comboBox_POS_currentIndexChanged(int index)
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


void AddNewWord::on_pushButton_saveDef_clicked()
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
                QString value = trimmedLine.mid(2);  // Assuming the "- " prefix should be removed
                output.push_back(value.toStdString());
            }
        }
        if(output.empty() && newWord->type&(1<<index))
            newWord->type^=(1<<index);
        else if(!output.empty())
            newWord->type|=(1<<index);
        newWord->def[index]=output;
        on_comboBox_POS_currentIndexChanged(index);
        QMessageBox::information(this,"Information","New definition has been saved!");
    }
}


void AddNewWord::on_pushButton_saveWord_clicked()
{
    QString raw=ui->lineEdit_word->text();
    std::string word=raw.toLower().toLocal8Bit().toStdString();
    if(raw.toLower()==QString::fromStdString(word)){
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
    else
        QMessageBox::warning(this,"Invalid input","Your input is not valid. Please type in solely ASCII characters!");
}

void AddNewWord::on_pushButton_add_clicked()
{
    dict->addWord(newWord,true);
    QMessageBox::information(this,"Information","New word has been added to dictionary!");
}

