#include "mainwindow.h"
#include "historyscreen.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dict dict;

    MainWindow w(&dict);
    w.show();
    return a.exec();
}
