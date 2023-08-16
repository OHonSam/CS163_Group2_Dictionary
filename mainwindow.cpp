#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFontDatabase>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>

MainWindow::MainWindow(Dict *dict, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dict(dict)
{
    ui->setupUi(this);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_dictVersion_currentIndexChanged(int index)
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
    ui->statusbar->showMessage("Switched successfully!",5000);
}

