#ifndef BEDIT_H
#define BEDIT_H

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

#endif // BEDIT_H
