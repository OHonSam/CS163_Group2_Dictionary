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

    void showDailyWord();

signals:
    void updateHistory();
    void updateFavList();
    void sendToSearchScreen(const std::string& input, Search::Type type);
    void sendToDefToWordScreen(const std::string& input);
    void sendToEditScreen(Word* word);

public slots:
    void updateCompleter();

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

    void on_pushButton_HistoryScreen_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_resetDailyWord_clicked();

    void on_pushButton_FavScreen_clicked();

    void on_pushButton_AddScreen_clicked();

    void on_pushButton_QuizScreen_clicked();

    void on_lineEdit_search_returnPressed();

    void on_pushButton_setFav_clicked(bool checked);

    void on_pushButton_editWord_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_expand_clicked();

private:
    Ui::HomeScreen *ui;
    QCompleter completer;

    QStringList suggestions;
    Word *dailyWord;

    QIcon heartIcon, heartFillIcon;
};

#endif // HOMESCREEN_H
