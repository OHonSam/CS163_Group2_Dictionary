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

private:
    Ui::HistoryScreen *ui;
    Dict *dict;
};

#endif // HISTORYSCREEN_H
