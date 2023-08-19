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
    , favListScreen(dict,this)
    , editScreen(dict,this)
    , addScreen(dict,this)
    , quizScreen(dict,this)
    , preScreen(Screen::Home)
    , curScreen(Screen::Home)
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
    ui->stackedWidget->addWidget(&favListScreen);
    ui->stackedWidget->addWidget(&editScreen);
    ui->stackedWidget->addWidget(&addScreen);
    ui->stackedWidget->addWidget(&quizScreen);

    // set default screen
    ui->stackedWidget->setCurrentIndex(Screen::Home);

    // connect signals and slot
    // 1. Switching screens
    connect(
        &homeScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &historyScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &favListScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &editScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &addScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &quizScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );
    connect(
        &searchScreen,SIGNAL(switchScreen(Screen::Type)),
        this,SLOT(switchScreen(Screen::Type))
    );

    // 2. Update history when searching
    connect(
        &homeScreen,SIGNAL(updateHistory(std::string,bool)),
        &historyScreen,SLOT(updateHistory(std::string,bool))
    );

    // 3. Send typed input to search screen
    connect(
        &homeScreen,SIGNAL(sendToSearchScreen(std::string)),
        &searchScreen,SLOT(receiveInputString(std::string))
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchScreen(Screen::Type id){
    std::swap(curScreen,preScreen);
    if(id!=Screen::GoBack) curScreen=id;
    ui->stackedWidget->setCurrentIndex(curScreen);
}
