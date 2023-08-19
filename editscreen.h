#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include "myscreen.h"

namespace Ui {
class EditScreen;
}

class EditScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit EditScreen(Dict *dict, QWidget *parent = nullptr);
    ~EditScreen();

public slots:
    void receiveWord(Word* word);

private slots:
    void on_comboBox_POS_currentIndexChanged(int index);

private:
    Ui::EditScreen *ui;

    Word *curWord;
};

#endif // EDITSCREEN_H
