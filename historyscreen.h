#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <QListWidgetItem>

#include "myscreen.h"

namespace Ui {
class HistoryScreen;
}

class HistoryScreen : public MyScreen
{
    Q_OBJECT
public:
    explicit HistoryScreen(Dict *dict, QWidget *parent = nullptr);
    ~HistoryScreen();

signals:
    void sendToSearchScreen(const std::string& word);

public slots:
    void update();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_remove_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::HistoryScreen *ui;
};

#endif // HISTORYSCREEN_H
