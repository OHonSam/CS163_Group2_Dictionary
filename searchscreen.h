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

public slots:
    void receiveInputString(const std::string& input, Search::Type type);

private slots:
    void on_pushButton_setFav_clicked(bool checked);

private:
    Ui::SearchScreen *ui;

    std::string input;

    QIcon heartIcon, heartFillIcon;
};

#endif // SEARCHSCREEN_H
