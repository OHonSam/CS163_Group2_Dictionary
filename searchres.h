#ifndef SEARCHRES_H
#define SEARCHRES_H

#include <QWidget>

namespace Ui {
class searchRes;
}

class searchRes : public QWidget
{
    Q_OBJECT

public:
    explicit searchRes(QWidget *parent = nullptr);
    ~searchRes();

private:
    Ui::searchRes *ui;
};

#endif // SEARCHRES_H
