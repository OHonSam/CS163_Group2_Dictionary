#ifndef SEARCHFORKEY_H
#define SEARCHFORKEY_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class SearchForKey;
}

class SearchForKey : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForKey(Dict *dict, QWidget *parent = nullptr);
    ~SearchForKey();

private:
    Ui::SearchForKey *ui;
    Dict *dict;
};

#endif // SEARCHFORKEY_H
