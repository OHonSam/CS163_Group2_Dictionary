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


void EditScreen::on_pushButton_save_clicked()
{
    QMessageBox::StandardButton rep;
    rep=QMessageBox::question(this,"Confirm",
        "The old definition will not be able to recovered.\nDo you want to save?",
                                QMessageBox::Yes|QMessageBox::No);
    if(rep==QMessageBox::Yes){

    }
}

