#ifndef SEARCHSCREEN_H
#define SEARCHSCREEN_H

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

public slots:
    void receiveInputString(const std::string& word);

private:
    Ui::SearchScreen *ui;
};

#endif // SEARCHSCREEN_H
