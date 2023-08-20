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

    Word* lazyUpdateWord();

public slots:
    void receiveWord(Word* word);

private slots:
    void on_comboBox_POS_currentIndexChanged(int index);

    void on_pushButton_saveDef_clicked();

    void on_pushButton_saveWord_clicked();

private:
    Ui::EditScreen *ui;

    Word *oldWord, *newWord;
};

#endif // EDITSCREEN_H
