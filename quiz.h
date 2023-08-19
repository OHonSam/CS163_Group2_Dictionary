#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>

#include <Dict.hpp>

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
    void switchToHomeScreen();

private slots:
    void on_pushButton_title_clicked();

private:
    Ui::Quiz *ui;
    Dict *dict;
};

#endif // QUIZ_H
