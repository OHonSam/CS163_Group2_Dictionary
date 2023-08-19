#ifndef QUIZ_H
#define QUIZ_H

#include "myscreen.h"

namespace Ui {
class Quiz;
}

class Quiz : public MyScreen
{
    Q_OBJECT

public:
    explicit Quiz(Dict *dict, QWidget *parent = nullptr);
    ~Quiz();

private:
    Ui::Quiz *ui;
};

#endif // QUIZ_H
