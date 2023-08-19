#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class AddNewWord;
}

class AddNewWord : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewWord(Dict *dict, QWidget *parent = nullptr);
    ~AddNewWord();

signals:
    void switchToHomeScreen();

private slots:
    void on_pushButton_title_clicked();

private:
    Ui::AddNewWord *ui;
    Dict *dict;
};

#endif // ADDNEWWORD_H
