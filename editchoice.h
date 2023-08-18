#ifndef EDITCHOICE_H
#define EDITCHOICE_H

#include <QWidget>

namespace Ui {
class EditChoice;
}

class EditChoice : public QWidget
{
    Q_OBJECT

public:
    explicit EditChoice(QWidget *parent = nullptr);
    ~EditChoice();

private:
    Ui::EditChoice *ui;
};

#endif // EDITCHOICE_H
