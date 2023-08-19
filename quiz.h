#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>

#include <Dict.hpp>
#include "screen.h"

namespace Ui {
class Quiz;
}

class Quiz : public QWidget
{
    Q_OBJECT

public:
    explicit Quiz(Dict *dict, QWidget *parent = nullptr);
    ~Quiz();

signals:
    void switchScreen(Screen::Type id);

private slots:
    void on_pushButton_title_clicked();

private:
    Ui::Quiz *ui;
    Dict *dict;
};

#endif // QUIZ_H
