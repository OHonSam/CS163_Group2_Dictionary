#ifndef SEARCHSCREEN_H
#define SEARCHSCREEN_H

#include <QWidget>

#include "html_creator.h"
#include <Dict.hpp>

namespace Ui {
class SearchScreen;
}

class SearchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SearchScreen(Dict *dict, QWidget *parent = nullptr);
    ~SearchScreen();

signals:
    void goBack();

public slots:
    void receiveWord(const std::string& word);

private slots:
    void on_pushButton_goBack_clicked();

private:
    Ui::SearchScreen *ui;
    Dict *dict;
};

#endif // SEARCHSCREEN_H
