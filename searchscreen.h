#ifndef SEARCHSCREEN_H
#define SEARCHSCREEN_H

#include <QIcon>

#include "myscreen.h"
#include "html_creator.h"

namespace Ui {
class SearchScreen;
}

class SearchScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit SearchScreen(Dict *dict, QWidget *parent = nullptr);
    ~SearchScreen();

signals:
    void updateFavList();
    void updateHistory();
    void updateCompleter();
    void sendToEditScreen(Word* word);

public slots:
    void receiveInputString(const std::string& input, Search::Type type);

private slots:
    void on_pushButton_setFav_clicked(bool checked);

    void on_pushButton_edit_clicked();

    void on_pushButton_remove_clicked();

private:
    Ui::SearchScreen *ui;

    Word *word;

    QIcon heartIcon, heartFillIcon;
};

#endif // SEARCHSCREEN_H
