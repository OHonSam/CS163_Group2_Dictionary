#ifndef SEARCHFORDEF_H
#define SEARCHFORDEF_H

#include <QWidget>

namespace Ui {
class SearchForDef;
}

class SearchForDef : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForDef(QWidget *parent = nullptr);
    ~SearchForDef();

private:
    Ui::SearchForDef *ui;
};

#endif // SEARCHFORDEF_H
