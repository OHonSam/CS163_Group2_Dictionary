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
    void updateFavList();
    void sendToSearchScreen(const std::string& word);

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

    void on_pushButton_HistoryScreen_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_resetDailyWord_clicked();

    void on_pushButton_FavScreen_clicked();

    void on_pushButton_EditScreen_clicked();

    void on_pushButton_AddScreen_clicked();

    void on_pushButton_QuizScreen_clicked();

    void on_lineEdit_search_returnPressed();

    void on_pushButton_setFav_clicked(bool checked);

private:
    Ui::HomeScreen *ui;
    QCompleter completer;

    QStringList suggestions;
    std::string dailyWord;

    QIcon heartIcon, heartFillIcon;

    void showDailyWord();
    void updateCompleter();
};

#endif // HOMESCREEN_H
