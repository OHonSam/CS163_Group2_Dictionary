#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>

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
    void switchToHistoryScreen();

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

    void on_pushButton_HistoryScreen_clicked();

private:
    Ui::HomeScreen *ui;

    Dict *dict;
};

#endif // HOMESCREEN_H
