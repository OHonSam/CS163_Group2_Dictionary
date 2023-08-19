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
public:
    explicit AddNewWord(Dict *dict, QWidget *parent = nullptr);
    ~AddNewWord();

private:
    Ui::AddNewWord *ui;
};

#endif // ADDNEWWORD_H
