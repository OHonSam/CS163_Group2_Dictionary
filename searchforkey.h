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

signals:
    void goBack();

public slots:
    void receiveWord(const std::string& word);

private slots:
    void on_pushButton_goBack_clicked();

private:
    Ui::SearchForKey *ui;
    Dict *dict;
};

#endif // SEARCHFORKEY_H
