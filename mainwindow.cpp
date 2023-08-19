#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFontDatabase>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QByteArray>

MainWindow::MainWindow(Dict *dict, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dict(dict)
    , homeScreen(dict,this)
    , historyScreen(dict,this)
    , searchScreen(dict,this)
{
    ui->setupUi(this);

    this->resize(DEF_WIDTH,DEF_HEIGHT);

    // Load fonts from the resource folder

    // 1. Audiowide
    QDir fontDir(":/font/font/Audiowide/");
    QStringList fontFiles = fontDir.entryList(QStringList() << "*.ttf", QDir::Files);
    foreach (const QString &fontFile, fontFiles) {
        QFile fontResource(":/font/font/Audiowide/" + fontFile);
        fontResource.open(QIODevice::ReadOnly);
        QByteArray fontData = fontResource.readAll();
        QFontDatabase::addApplicationFontFromData(fontData);
    }

    // 2. Comfortaa
    fontDir = QDir(":/font/font/Comfortaa/static/");
    fontFiles = fontDir.entryList(QStringList() << "*.ttf", QDir::Files);
    foreach (const QString &fontFile, fontFiles) {
        QFile fontResource(":/font/font/Comfortaa/static/" + fontFile);
        fontResource.open(QIODevice::ReadOnly);
        QByteArray fontData = fontResource.readAll();
        QFontDatabase::addApplicationFontFromData(fontData);
    }

    // set stack widget
    ui->stackedWidget->addWidget(&homeScreen);
    ui->stackedWidget->addWidget(&historyScreen);
    ui->stackedWidget->addWidget(&searchScreen);

    // set default screen
    ui->stackedWidget->setCurrentIndex(Screens::Home);

    // connect signals and slot
    connect(
        &homeScreen,SIGNAL(switchToHistoryScreen()),
        this,SLOT(switchToHistoryScreen())
    );
    connect(
        &historyScreen,SIGNAL(goBack()),
        this,SLOT(switchToHomeScreen())
    );
    connect(
        &homeScreen,SIGNAL(updateHistory(std::string,bool)),
        &historyScreen,SLOT(updateHistory(std::string,bool))
    );
    connect(
        &homeScreen,SIGNAL(switchToScreenScreen(std::string)),
        this,SLOT(switchToSearchScreen(std::string))
    );
    connect(
        &searchScreen,SIGNAL(goBack()),
        this,SLOT(switchToHomeScreen())
    );
    connect(
        this,SIGNAL(giveWord(std::string)),
        &searchScreen,SLOT(receiveWord(std::string))
    );
    connect(
        &homeScreen,SIGNAL(switchDataSet()),
        &homeScreen,SLOT(updateCompleter())
    );
    connect(
        &homeScreen,SIGNAL(switchDataSet()),
        &searchScreen,SLOT(updateCompleter())
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToHistoryScreen(){
    ui->stackedWidget->setCurrentIndex(Screens::History);
}

void MainWindow::switchToHomeScreen(){
    ui->stackedWidget->setCurrentIndex(Screens::Home);
}

void MainWindow::switchToSearchScreen(const std::string& word){
    ui->stackedWidget->setCurrentIndex(Screens::Search);
    emit giveWord(word);
}
