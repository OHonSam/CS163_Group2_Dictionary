#include "favlistscreen.h"
#include "ui_favlistscreen.h"

FavListScreen::FavListScreen(Dict *dict, QWidget *parent) :
    MyScreen(dict,Screen::FavList,parent),
    ui(new Ui::FavListScreen)
{
    ui->setupUi(this);

    update();
}

FavListScreen::~FavListScreen()
{
    delete ui;
}

void FavListScreen::update(){
    ui->listWidget->clear();
    std::vector<std::string> v=dict->getFav();
    for(int i=0; i<v.size(); i++)
        ui->listWidget->addItem(QString::number(i+1)+". "+QString::fromStdString(v[i]));
}

