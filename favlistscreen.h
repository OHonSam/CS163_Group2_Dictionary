#ifndef FAVLISTSCREEN_H
#define FAVLISTSCREEN_H

#include <QListWidgetItem>

#include "myscreen.h"

namespace Ui {
class FavListScreen;
}

class FavListScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit FavListScreen(Dict *dict, QWidget *parent = nullptr);
    ~FavListScreen();

signals:
    void sendToSearchScreen(const std::string& word);

public slots:
    void update();

private slots:
    void on_pushButton_remove_clicked();

    void on_pushButton_clear_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::FavListScreen *ui;
};

#endif // FAVLISTSCREEN_H
