#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class FavListScreen;
}

class HistoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryScreen(Dict *dict, QWidget *parent = nullptr);
    ~HistoryScreen();

signals:
    void goBack();
    void switchToHomeScreen();

public slots:
    void updateHistory(const std::string& word, bool isAdd);

private slots:
    void on_pushButton_goBack_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_title_clicked();

private:
    Ui::FavListScreen *ui;
    Dict *dict;

    void update();
};

#endif // HISTORYSCREEN_H
