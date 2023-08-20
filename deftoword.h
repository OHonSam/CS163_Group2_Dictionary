#ifndef DEFTOWORD_H
#define DEFTOWORD_H

#include "myscreen.h"

namespace Ui {
class DefToWord;
}

class DefToWord : public MyScreen
{
    Q_OBJECT

public:
    explicit DefToWord(Dict *dict, QWidget *parent = nullptr);
    ~DefToWord();

public slots:
    void receiveInput(const std::string& input);

private:
    Ui::DefToWord *ui;
};

#endif // DEFTOWORD_H
