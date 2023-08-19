#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <Dict.hpp>
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

public slots:
    void updateHistory(const std::string& word, bool isAdd);

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_remove_clicked();

private:
    Ui::HistoryScreen *ui;

    void update();
};

#endif // HISTORYSCREEN_H
