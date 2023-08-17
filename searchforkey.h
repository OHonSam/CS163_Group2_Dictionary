#ifndef SEARCHFORKEY_H
#define SEARCHFORKEY_H

#include <QWidget>

namespace Ui {
class SearchForKey;
}

class SearchForKey : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForKey(QWidget *parent = nullptr);
    ~SearchForKey();

private:
    Ui::SearchForKey *ui;
};

#endif // SEARCHFORKEY_H
