#ifndef DEFTOWORD_H
#define DEFTOWORD_H

#include "myscreen.h"

#include <QListWidgetItem>

namespace Ui {
class DefToWord;
}

class DefToWord : public MyScreen
{
    Q_OBJECT

public:
    explicit DefToWord(Dict *dict, QWidget *parent = nullptr);
    ~DefToWord();

signals:
    void sendToSearchScreen(const std::string& input, Search::Type type=Search::ForDef);

public slots:
    void receiveInput(const std::string& input);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DefToWord *ui;
};

#endif // DEFTOWORD_H
