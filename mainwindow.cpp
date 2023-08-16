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
    ui->stackedWidget->addWidget(new HomeScreen(dict,this));

    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
