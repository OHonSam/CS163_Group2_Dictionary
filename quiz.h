#ifndef QUIZ_H
#define QUIZ_H

#include "myscreen.h"

namespace Ui {
class Quiz;
}

namespace MC{
enum Type{
    Def, // 1 def 4 words
    Word, // 1 word 4 defs
};
}

class Quiz : public MyScreen
{
    Q_OBJECT

public:
    explicit Quiz(Dict *dict, QWidget *parent = nullptr);
    ~Quiz();

private slots:
    void on_pushButton_newQuiz_clicked();

private:
    Ui::Quiz *ui;

    const int NUMC=4;

    int correctId;
    std::vector<Word*> words;
};

#endif // QUIZ_H
