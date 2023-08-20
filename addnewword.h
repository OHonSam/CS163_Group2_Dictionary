#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QWidget>

#include <Dict.hpp>
#include "myscreen.h"

namespace Ui {
class AddNewWord;
}

class AddNewWord : public MyScreen
{
    Q_OBJECT

public:
    explicit AddNewWord(Dict *dict, QWidget *parent = nullptr);
    ~AddNewWord();

private slots:
    void on_pushButton_discard_clicked();

    void on_pushButton_saveWord_clicked();

    void on_pushButton_saveDef_clicked();

    void on_comboBox_POS_currentIndexChanged(int index);

    void on_pushButton_add_clicked();

private:
    Ui::AddNewWord *ui;
    Word* newWord;
};

#endif // ADDNEWWORD_H
