#include "mainwindow.h"

#include <QApplication>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    HistoryScreen h;
    SearchForDef sfd;
    sfd.show();
    return a.exec();
}
