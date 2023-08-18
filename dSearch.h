#ifndef DSEARCH_H
#define DSEARCH_H

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

#endif // DSEARCH_H
