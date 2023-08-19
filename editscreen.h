#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include <QWidget>

#include <Dict.hpp>

namespace Ui {
class EditScreen;
}

class EditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit EditScreen(Dict *dict, QWidget *parent = nullptr);
    ~EditScreen();

signals:
    void switchToHomeScreen();

private slots:
    void on_pushButton_title_clicked();

private:
    Ui::EditScreen *ui;
    Dict *dict;
};

#endif // EDITSCREEN_H
