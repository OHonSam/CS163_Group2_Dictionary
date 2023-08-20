#ifndef QUIZ_H
#define QUIZ_H

#include "myscreen.h"

#include <QPushButton>

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

    void on_pushButton_c0_clicked();

    void on_pushButton_c1_clicked();

    void on_pushButton_c2_clicked();

    void on_pushButton_c3_clicked();

private:
    const int NUMC=4;

    QString normalStyle="padding: 20px;"
                           "border-width : 2px;"
                           "border-style:solid;"
                           "border-radius: 20px;"
                           "min-height: 20px;"
                           "min-width: 20px;"
                           "background-color: rgb(233, 240, 250);"
                           "border-color: rgb(99, 112, 243);"
                           "font: 13pt \"Comfortaa\";"
                           "color: rgb(56, 64, 139);";

    QString correctStyle="padding: 20px;"
                        "border-width : 2px;"
                        "border-style:solid;"
                        "border-radius: 20px;"
                        "min-height: 20px;"
                        "min-width: 20px;"
                        "background-color: green;"
                        "border-color: rgb(99, 112, 243);"
                        "font: 13pt \"Comfortaa\";"
                        "color: white;";

    QString incorrectStyle="padding: 20px;"
                           "border-width : 2px;"
                           "border-style:solid;"
                           "border-radius: 20px;"
                           "min-height: 20px;"
                           "min-width: 20px;"
                           "background-color: red;"
                           "border-color: rgb(99, 112, 243);"
                           "font: 13pt \"Comfortaa\";"
                           "color: white;";

    Ui::Quiz *ui;

    int correctId;
    std::vector<Word*> words;

    QPushButton* getButton(int id);
    void considerChoice(int id);
};

#endif // QUIZ_H
