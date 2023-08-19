#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QCompleter>

#include "myscreen.h"

namespace Ui {
class HomeScreen;
}

class HomeScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit HomeScreen(Dict *dict, QWidget *parent = nullptr);
    ~HomeScreen();

signals:
    void updateHistory(const std::string& word, bool isAdd=true);
    void sendToSearchScreen(const std::string& word);

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

    void on_pushButton_HistoryScreen_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_resetDailyWord_clicked();

    void on_pushButton_FavScreen_clicked();

    void on_pushButton_EditScreen_clicked();

    void on_pushButton_AddScreen_clicked();

private:
    Ui::HomeScreen *ui;
    QCompleter completer;

    QStringList suggestions;

    void showDailyWord();
    void updateCompleter();
};

#endif // HOMESCREEN_H
