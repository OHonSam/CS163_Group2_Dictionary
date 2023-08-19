#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QWidget>

namespace Ui {
class EditScreen;
}

class AddNewWord : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewWord(QWidget *parent = nullptr);
    ~AddNewWord();

private:
    Ui::EditScreen *ui;
};

#endif // ADDNEWWORD_H
