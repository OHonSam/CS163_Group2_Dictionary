#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QCompleter>

#include <Dict.hpp>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(Dict *dict, QWidget *parent = nullptr);
    ~HomeScreen();

signals:
    void switchDataSet();

    void switchToHistoryScreen();
    void updateHistory(const std::string& word, bool isAdd=true);

    void switchToSearchForKeyScreen(const std::string& word);

public slots:
    void updateCompleter();

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

    void on_pushButton_HistoryScreen_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_resetDailyWord_clicked();

private:
    Ui::HomeScreen *ui;
    QCompleter completer;

    Dict *dict;
    QStringList suggestions;

    void showDailyWord();
};

#endif // HOMESCREEN_H
