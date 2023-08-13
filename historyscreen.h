#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <QWidget>

namespace Ui {
class HistoryScreen;
}

class HistoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryScreen(QWidget *parent = nullptr);
    ~HistoryScreen();

private:
    Ui::HistoryScreen *ui;
};

#endif // HISTORYSCREEN_H
