#ifndef SEARCHFORKEY_H
#define SEARCHFORKEY_H

#include <QWidget>
#include "html_creator.h"

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

signals:
    void goBack();

private slots:
    void on_pushButton_goBack_clicked();

private:
    Ui::SearchForKey *ui;
    Dict *dict;
};

#endif // SEARCHFORKEY_H
