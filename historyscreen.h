#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class HistoryScreen;
}

class HistoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryScreen(Dict *dict, QWidget *parent = nullptr);
    ~HistoryScreen();

signals:
    void goBack();

public slots:
    void updateHistory(const std::string& word, bool isAdd);

private slots:
    void on_pushButton_goBack_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::HistoryScreen *ui;
    Dict *dict;

    void update();
};

#endif // HISTORYSCREEN_H
