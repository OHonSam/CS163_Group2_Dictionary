#ifndef SEARCHFORDEF_H
#define SEARCHFORDEF_H

#include <QWidget>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>
#include "html_creator.h"

#include <Dict.hpp>

namespace Ui {
class SearchForDef;
}

class SearchForDef : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForDef(Dict *dict, QWidget *parent = nullptr);
    ~SearchForDef();

signals:
    void goBack();

public slots:
    void receiveWord(const std::string& word);
    void updateCompleter();

private slots:
    void on_pushButton_goBack_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::SearchForDef *ui;
    Dict *dict;

    QCompleter completer;
    QStringList suggestions;
};

#endif // SEARCHFORDEF_H
